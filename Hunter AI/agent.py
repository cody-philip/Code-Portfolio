from vector2d import Vector2D
from vector2d import Point2D
from graphics import egi, KEY, closed_shape, line_with_arrow
from math import sin, cos, radians
from random import random, randrange, uniform
from path import Path

AGENT_MODES = {
    KEY._1: 'seek',
    KEY._2: 'arrive_slow',
    KEY._3: 'arrive_normal',
    KEY._4: 'arrive_fast',
    KEY._5: 'flee',
    KEY._6: 'pursuit',
    KEY._7: 'follow_path',
    KEY._8: 'wander',
    KEY._9: 'emergent',
}


class Agent(object):
    DECELERATION_SPEEDS = {
        'slow': 0.9,
        'normal': 0.7,
        'fast': 0.5,
    }

    def __init__(self, world=None, scale=30.0, mass=1.0, mode='seek'):
        self.world = world
        self.mode = mode
        direction = radians(random() * 360)
        self.pos = Vector2D(randrange(world.cx), randrange(world.cy))
        self.vel = Vector2D()
        self.heading = Vector2D(sin(direction), cos(direction))
        self.side = self.heading.perp()
        self.scale = Vector2D(scale, scale)  # easy scaling of agent size
        self.force = Vector2D()  # current steering force
        self.accel = Vector2D()  # current acceleration due to force
        self.mass = mass

        # data for drawing this agent
        self.color = 'AQUA'
        self.vehicle_shape = [
            Point2D(-0.7, 0.6),
            Point2D(0.7, 0.0),
            Point2D(-0.7, -0.6),
            Point2D(-0.5, 0.0)
        ]
        # path to follow
        self.path = Path()
        self.randomise_path()
        self.waypoint_threshold = 30.0

        # wander details
        self.wander_target = Vector2D(1, 0)
        self.wander_dist = 1.0 * scale
        self.wander_radius = 1.0 * scale
        self.wander_jitter = 10.0 * scale
        self.bRadius = scale

        # limits?
        self.max_speed = 10 * scale
        self.max_force = 500.0

        # debug draw info?
        self.show_info = True

        self.cohesion = 1
        self.separation = 1
        self.alignment = 1
        self.neighborHood = 150

    def randomise_path(self):
        cx = self.world.cx
        cy = self.world.cy
        margin = min(cx, cy) * (1 / 6)
        self.path.create_random_path(5, margin, margin, cx - margin, cy - margin)

    def calculate(self, delta):
        # calculate the current steering force
        mode = self.mode
        if mode == 'seek':
            force = self.seek(self.world.target)
        elif mode == 'arrive_slow':
            force = self.arrive(self.world.target, 'slow')
        elif mode == 'arrive_normal':
            force = self.arrive(self.world.target, 'normal')
        elif mode == 'arrive_fast':
            force = self.arrive(self.world.target, 'fast')
        elif mode == 'flee':
            force = self.flee(self.world.target)
        elif mode == 'pursuit':
            force = self.pursuit(self.world.hunter)
        elif mode == 'wander':
            force = self.wander(delta)
        elif mode == 'follow_path':
            force = self.follow_path()
        elif mode == 'emergent':
            force = self.emergentChase(delta, self.world.hunter)
        else:
            force = Vector2D()
        self.force = force
        return force

    def checkISNeighbor(self, agent):
        dist = agent.pos - self.pos
        # if agent is not self
        if dist.length() < self.neighborHood:
            return True
        else:
            return False

    def countNeighbors(self):
        neighborCount = 0
        for agent in self.world.agents:
            if self.checkISNeighbor(agent):
                neighborCount += 1
        neighborCount -= 1
        return neighborCount

    def calculateAlignment(self):
        v = Vector2D()
        neighborCount = 0
        for agent in self.world.agents:
            if self.checkISNeighbor(agent):
                neighborCount += 1
                v.x += agent.vel.x
                v.y += agent.vel.y
        neighborCount -= 1
        # if neighborCount == 0:
        #    return Vector2D()
        if neighborCount != 0:
            v.x /= neighborCount
            v.y /= neighborCount
            v.normalise()
        return v

    def calculateCohesion(self):
        v = Vector2D()
        neighborCount = 0
        for agent in self.world.agents:
            if self.checkISNeighbor(agent):
                neighborCount += 1
                v.x += agent.pos.x
                v.y += agent.pos.y
        neighborCount -= 1
        if neighborCount == 0:
            return Vector2D()
        if neighborCount != 0:
            v.x /= neighborCount
            v.y /= neighborCount
            v = Vector2D(v.x - self.pos.x, v.y - self.pos.y)
            v.normalise()
        return v

    def calculateSeparation(self):
        v = Vector2D()
        neighborCount = 0
        for agent in self.world.agents:
            if self.checkISNeighbor(agent):
                neighborCount += 1
                v.x += agent.pos.x - self.pos.x
                v.y += agent.pos.y - self.pos.y
        neighborCount -= 1
        if neighborCount == 0:
            return Vector2D()
        if neighborCount != 0:
            v.x /= neighborCount
            v.y /= neighborCount
            v = Vector2D(v.x - self.pos.x, v.y - self.pos.y)
            v.x *= -1
            v.y *= -1
            v.normalise()
        return v

    def update(self, delta):
        """ update vehicle position and orientation """
        # calculate and set self.force to be applied
        # force = self.calculate()
        force = self.calculate(delta)  # <-- delta needed for wander
        force.truncate(self.max_force)
        # limit force? <-- for wander
        # ...
        # determine the new acceleration
        self.accel = force / self.mass  # not needed if mass = 1.0
        # new velocity
        self.vel += self.accel * delta
        # check for limits of new velocity
        self.vel.truncate(self.max_speed)
        # update position
        self.pos += self.vel * delta
        # update heading is non-zero velocity (moving)
        if self.vel.length_sq() > 0.00000001:
            self.heading = self.vel.get_normalised()
            self.side = self.heading.perp()
        # treat world as continuous space - wrap new position if needed
        self.world.wrap_around(self.pos)
        if self.max_speed < 0:
            self.max_speed = 0

    def render(self):
        """ Draw the triangle agent with color"""
        # draw the path if it exists and the mode is followed
        if self.mode == 'follow_path':
            self.path.render()
            # pass

        # draw the ship
        egi.set_pen_color(name=self.color)
        pts = self.world.transform_points(self.vehicle_shape, self.pos, self.heading, self.side, self.scale)
        # draw it!
        closed_shape(pts)

        # add some handy debug drawing info lines - force and velocity
        if self.show_info:
            # draw wander info?
            if self.mode == 'wander' or self.mode == 'emergent':
                wnd_pos = Vector2D(self.wander_dist, 0)
                wld_pos = self.world.transform_point(wnd_pos, self.pos, self.heading, self.side)

                egi.grey_pen()
                egi.add_circle(wld_pos, self.wander_radius)

                egi.red_pen()
                wnd_pos = (self.wander_target + Vector2D(self.wander_dist, 0))
                wld_pos = self.world.transform_point(wnd_pos, self.pos, self.heading, self.side)
                egi.add_circle(wld_pos, 3)

                egi.blue_pen()
                egi.add_circle(self.pos, self.neighborHood)

                egi.green_pen()
                line_with_arrow(self.pos, self.pos + self.emergent(), 5)

                egi.pink_pen()
                line_with_arrow(self.pos, self.pos + (self.calculateAlignment() * (self.alignment * 10)), 5)

                egi.purple_pen()
                line_with_arrow(self.pos, self.pos + (self.calculateSeparation() * (self.separation * 10)), 5)

                egi.orange_pen()
                line_with_arrow(self.pos, self.pos + (self.calculateCohesion() * (self.cohesion * 10)), 5)
                # pass
            s = 0.5  # <-- scaling factor
            # force
            egi.red_pen()
            line_with_arrow(self.pos, self.pos + self.force * s, 5)
            # velocity
            egi.grey_pen()
            line_with_arrow(self.pos, self.pos + self.vel * s, 5)
            # net (desired) change
            egi.white_pen()
            line_with_arrow(self.pos + self.vel * s, self.pos + (self.force + self.vel) * s, 5)
            line_with_arrow(self.pos, self.pos + (self.force + self.vel) * s, 5)

    def speed(self):
        return self.vel.length()

    # --------------------------------------------------------------------------

    def seek(self, target_pos):
        """ move towards target position """
        desired_vel = (target_pos - self.pos).normalise() * self.max_speed
        return desired_vel - self.vel

    def flee(self, hunter_pos):
        """ move away from hunter position """
        to_target = hunter_pos - self.pos
        if to_target.length() < 150:
            desired_vel = (hunter_pos - self.pos).normalise() * self.max_speed
            return -(desired_vel - self.vel)
        else:
            return Vector2D()

    def arrive(self, target_pos, speed):
        """ this behaviour is similar to seek() but it attempts to arrive at
            the target position with a zero velocity"""
        deceleration_rate = self.DECELERATION_SPEEDS[speed]
        to_target = target_pos - self.pos
        dist = to_target.length()
        if dist > 0:
            speed = dist / deceleration_rate
            speed = min(speed, self.max_speed)
            desired_vel = to_target * (speed / dist)
            return desired_vel - self.vel
        return Vector2D(0, 0)

    def pursuit(self, evader):
        """ this behaviour predicts where an agent will be in time T and seeks
            towards that point to intercept it. """
        if len(self.world.agents) > 1:
            if self == evader:
                return self.seek(self.world.agents[1].pos)
            elif self != evader:
                return self.flee(self.world.agents[0].pos)
        # OPTIONAL EXTRA... pursuit (you'll need something to pursue!)
        return Vector2D()

    def wander(self, delta):
        """ Random wandering using a projected jitter circle. """
        wt = self.wander_target

        jitter_tts = self.wander_jitter * delta

        wt += Vector2D(uniform(-1, 1) * jitter_tts, uniform(-1, 1) * jitter_tts)

        wt.normalise()

        wt *= self.wander_radius

        target = wt + Vector2D(self.wander_dist, 0)

        wld_target = self.world.transform_point(target, self.pos, self.heading, self.side)

        # fix this
        # tmp = self.world.transform_point(self.emergent(), self.pos, self.heading, self.side)

        if self.countNeighbors() == 0:
            return self.seek(wld_target)

        return self.seek(wld_target) + self.emergent()

    def follow_path(self):
        if self.path.is_finished():
            return self.arrive(self.path.current_pt(), 'slow')
        else:
            to_target = self.path.current_pt() - self.pos
            dist = to_target.length()
            if dist < self.waypoint_threshold:
                self.path.inc_current_pt()
            return self.seek(self.path.current_pt())

    def emergent(self):
        v = Vector2D()
        alignment = self.calculateAlignment()
        cohesion = self.calculateCohesion()
        separation = self.calculateSeparation()
        v += self.vel + (alignment * (self.alignment * 100)) + (cohesion * (self.cohesion * 100)) + (
                separation * (self.separation * 100))
        return v

    def emergentChase(self, delta, evader):
        if len(self.world.agents) > 1:
            if self == evader:
                return self.seek(self.world.target)
            elif self != evader:
                return self.wander(delta) + self.flee(evader.pos)
        return Vector2D()
