import graphics
from graphics import egi, KEY
from pyglet import window, clock
from pyglet.gl import *

from vector2d import Vector2D
from world import World
from agent import Agent, AGENT_MODES  # Agent with seek, arrive, flee and pursuit


def on_mouse_press(x, y, button):
    if button == 1:  # left
        world.target = Vector2D(x, y)


def on_key_press(symbol):
    if symbol == KEY.P:
        world.paused = not world.paused
    elif symbol == KEY.A:
        world.hunter = world.agents[0]
        world.agents[0].color = 'RED'
        world.agents.append(Agent(world))
    elif symbol in AGENT_MODES:
        for agent in world.agents:
            agent.mode = AGENT_MODES[symbol]
    elif symbol == KEY.UP:
        for agent in world.agents:
            agent.mass += 1
    elif symbol == KEY.DOWN:
        for agent in world.agents:
            agent.mass -= 1
    elif symbol == KEY.RIGHT:
        for agent in world.agents:
            agent.max_speed += 100
    elif symbol == KEY.LEFT:
        for agent in world.agents:
            agent.max_speed -= 100
    elif symbol == KEY.M:
        for agent in world.agents:
            agent.randomise_path()
    elif symbol == KEY.L:
        for agent in world.agents:
            agent.path.set_looped()
    elif symbol == KEY.U:
        for agent in world.agents:
            agent.alignment += 1
    elif symbol == KEY.J:
        for agent in world.agents:
            agent.alignment -= 1
    elif symbol == KEY.Y:
        for agent in world.agents:
            agent.cohesion += 1
    elif symbol == KEY.H:
        for agent in world.agents:
            agent.cohesion -= 1
    elif symbol == KEY.T:
        for agent in world.agents:
            agent.separation += 1
    elif symbol == KEY.G:
        for agent in world.agents:
            agent.separation -= 1
    elif symbol == KEY.R:
        for agent in world.agents:
            agent.neighborHood += 10
    elif symbol == KEY.F:
        for agent in world.agents:
            agent.neighborHood -= 10

    # LAB 06 TASK 1: Reset all paths to new random ones
    # ...

    # Toggle debug force line info on the agent
    elif symbol == KEY.I:
        for agent in world.agents:
            agent.show_info = not agent.show_info


def on_resize(cx, cy):
    world.cx = cx
    world.cy = cy


if __name__ == '__main__':

    # create a pyglet window and set glOptions
    win = window.Window(width=800, height=600, vsync=True, resizable=True)
    glEnable(GL_BLEND)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
    # needed so that egi knows where to draw
    egi.InitWithPyglet(win)
    # prep the fps display
    # fps_display = clock.ClockDisplay()
    # register key and mouse event handlers
    win.push_handlers(on_key_press)
    win.push_handlers(on_mouse_press)
    win.push_handlers(on_resize)

    # create a world for agents
    world = World(500, 500)
    # add one agent
    world.agents.append(Agent(world))
    # unpause the world ready for movement
    world.paused = False

    while not win.has_exit:
        win.dispatch_events()
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        # show nice FPS bottom right (default)
        graphics.BATCH.draw()
        egi.clear_shapes()
        delta = clock.tick()
        world.update(delta)
        world.render()
        # fps_display.draw()
        # swap the double buffer
        win.flip()
