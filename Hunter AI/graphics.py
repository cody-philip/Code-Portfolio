from pyglet.gl import *
from pyglet import window
from pyglet.shapes import *

# from math import cos, sin, pi

BATCH = pyglet.graphics.Batch()

KEY = window.key  # the key codes

COLOR_NAMES = {
    'BLACK': (0, 0, 0),
    'WHITE': (225, 225, 225),
    'RED': (225, 0, 0),
    'GREEN': (0, 225, 0),
    'BLUE': (0, 0, 225),
    'GREY': (135, 135, 135),
    'PINK': (225, 158, 158),
    'YELLOW': (225, 225, 0),
    'ORANGE': (225, 158, 0),
    'PURPLE': (225, 0, 158),
    'BROWN': (113, 79, 0),
    'AQUA': (0, 225, 225),
    'DARK_GREEN': (0, 90, 0),
    'LIGHT_BLUE': (135, 135, 225),
    'LIGHT_GREY': (180, 180, 180),
    'LIGHT_PINK': (225, 203, 203)
}


def closed_shape(points):
    if len(points) < 2:
        return
    pts = [(p.x, p.y) for p in points]
    pts = ((GLfloat * 2) * len(pts))(*pts)

    i = 0
    while i < len(pts):
        if i is not len(pts) - 1:
            egi.add_line(pts[i][0], pts[i][1], pts[i + 1][0], pts[i + 1][1])
        else:
            egi.add_line(pts[i][0], pts[i][1], pts[0][0], pts[0][1])
        i = i + 1


def polyline(points):
    if len(points) < 2:
        return
    pts = [(p.x, p.y) for p in points]  # convert to list of tuples
    pts = ((GLfloat * 2) * len(pts))(*pts)  # convert to GLfloat list

    i = 0
    while i < len(pts):
        if i is not len(pts) - 1:
            egi.add_line(pts[i][0], pts[i][1], pts[i + 1][0], pts[i + 1][1])
        i = i + 1


def line_with_arrow(v1, v2, size):
    norm = v2 - v1
    norm.normalise()
    # calculate where arrow is attached
    xpoint = v2 - (norm * size)
    # calculate the two extra points required to make the arrowhead
    ap1 = xpoint + (norm.perp() * 0.4 * size)
    ap2 = xpoint - (norm.perp() * 0.4 * size)
    # draw triangle for head
    closed_shape((v1, v2, ap1, ap2))


def cross(pos, diameter):
    d = diameter
    x, y = pos.x, pos.y

    egi.add_line(x - d, y - d, x + d, y + d)
    egi.add_line(x + d, y - d, x - d, y + d)


class EasyGraphics(object):

    def __init__(self):
        # current "pen" colour of lines
        self.text = []
        self.window = None
        self.curr_color = None
        self.pen_color = (225, 0, 0)
        self.stroke = 1.0  # - thickness the default
        self.shapes = []

    def InitWithPyglet(self, win):
        self.set_pen_color(self.pen_color)
        self.set_stroke(self.stroke)
        self.window = win

    def add_line(self, x1, y1, x2, y2):
        tmp = Line(x1, y1, x2, y2, width=1, color=self.curr_color, batch=BATCH)
        self.shapes.append(tmp)

    def add_circle(self, pos, r, x=None, y=None):
        if pos is not None:
            x, y = pos.x, pos.y
        tmp = Arc(x, y, r, color=self.curr_color, batch=BATCH)
        # tmp = Circle(x, y, r, color=self.curr_color, batch=BATCH)
        self.shapes.append(tmp)

    def clear_shapes(self):
        self.shapes.clear()

    # ----- COLOUR/STROKE STUFF -----
    def set_pen_color(self, color=None, name=None):
        if name is not None:
            color = COLOR_NAMES[name]
        self.curr_color = color

    def red_pen(self):
        self.set_pen_color(name='RED')

    def blue_pen(self):
        self.set_pen_color(name='BLUE')

    def green_pen(self):
        self.set_pen_color(name='GREEN')

    def black_pen(self):
        self.set_pen_color(name='BLACK')

    def white_pen(self):
        self.set_pen_color(name='WHITE')

    def grey_pen(self):
        self.set_pen_color(name='GREY')

    def aqua_pen(self):
        self.set_pen_color(name='AQUA')

    def orange_pen(self):
        self.set_pen_color(name='ORANGE')

    def pink_pen(self):
        self.set_pen_color(name="PINK")

    def purple_pen(self):
        self.set_pen_color(name="PURPLE")

    def set_stroke(self, stroke):
        self.stroke = stroke
        # glLineWidth(self.stroke)

    # ----- TEXT METHODS -----
    def text_color(self, color=None, name=None):
        """ Colour is a tuple (R,G,B,A) with values from 0.0 to 1.0 """
        if name is not None:
            color = COLOR_NAMES[name]
        self.text.color = color  #

    def text_at_pos(self, x, y, text):
        label = pyglet.text.Label()
        label.text = text
        label.x = x
        label.y = self.window.height + y if y < 0 else y
        label.draw()


# create an instance for anyone to use
egi = EasyGraphics()
