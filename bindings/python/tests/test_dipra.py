import dipra
from PIL import Image
import numpy as np


def test_polygon():
    polygon = [
        (0.0, 0.0),
        (9.0, 5.0),
        (2.0, 8.0),
    ]
    x, y, alpha = dipra.rasterize(polygon)

    im = np.zeros((8, 9))
    im[y, x] = alpha

    im = Image.fromarray((im * 255).astype(np.uint8))
    im.save("images/1.png")

