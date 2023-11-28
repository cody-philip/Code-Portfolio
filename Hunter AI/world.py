from vector2d import Vector2D
from matrix33 import Matrix33
from graphics import egi, cross








class World(object):
    def __init__(self, cx, cy):
        self.cx = cx
        self.cy = cy
        self.target = Vector2D(cx / 2, cy / 2)
        self.hunter = None
        self.agents = []
        self.paused = True
        self.show_info = True

    def transform_points(self, points, pos, forward, side, scale):
        """ Transform the given list of points, using the provided position,
            direction and scale, to object world space. """
        # make a copy of original points (so we don't trash them)
        wld_pts = [pt.copy() for pt in points]
        # create a transformation matrix to perform the operations
        mat = Matrix33()
        # scale,
        mat.scale_update(scale.x, scale.y)
        # rotate
        mat.rotate_by_vectors_update(forward, side)
        # and translate
        mat.translate_update(pos.x, pos.y)
        # now transform all the points (vertices)
        mat.transform_vector2d_list(wld_pts)
        # done
        return wld_pts

    def transform_point(self, point, pos, forward, side):
        wld_pt = point.copy()

        mat = Matrix33()

        mat.rotate_by_vectors_update(forward, side)

        mat.translate_update(pos.x, pos.y)

        mat.transform_vector2d(wld_pt)

        return wld_pt

    def update(self, delta):
        if not self.paused:
            for agent in self.agents:
                agent.update(delta)

    def render(self):
        for agent in self.agents:
            agent.render()

        if self.target:
            egi.red_pen()
            cross(self.target, 10)

        if self.show_info:
            # count = 0
            infoText = ', '.join(set(agent.mode for agent in self.agents))
            egi.white_pen()
            egi.text_at_pos(0, 0, infoText)
            infoText = 'Alignment: ' + str(set(agent.alignment for agent in self.agents))
            egi.text_at_pos(0, 15, infoText)
            infoText = 'Cohesion: ' + str(set(agent.cohesion for agent in self.agents))
            egi.text_at_pos(0, 30, infoText)
            infoText = 'Separation: ' + str(set(agent.separation for agent in self.agents))
            egi.text_at_pos(0, 45, infoText)
            infoText = 'Neighbour Hood: ' + str(set(agent.neighborHood for agent in self.agents))
            egi.text_at_pos(0, 60, infoText)
            infoText = 'Max Speed: ' + str(set(agent.max_speed for agent in self.agents))
            egi.text_at_pos(0, 75, infoText)
            # for agent in self.agents:
            #    count += 15
            #    tmp = str(agent.vel.x) + ", " + str(agent.vel.y)
            #    egi.text_at_pos(0, 0 + count, tmp)

    def wrap_around(self, pos):
        """ Treat world as a toroidal space. Updates parameter object pos """
        max_x, max_y = self.cx, self.cy
        if pos.x > max_x:
            pos.x = pos.x - max_x
        elif pos.x < 0:
            pos.x = max_x - pos.x
        if pos.y > max_y:
            pos.y = pos.y - max_y
        elif pos.y < 0:
            pos.y = max_y - pos.y
