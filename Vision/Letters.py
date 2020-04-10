# Untitled - By: diego - Tue Feb 4 2020

import time, sensor, image, pyb
from image import SEARCH_EX, SEARCH_DS

# Reset sensor
sensor.reset()

# Set sensor settings
sensor.set_contrast(1)
sensor.set_gainceiling(16)
# Max resolution for template matching with SEARCH_EX is QQVGA
sensor.set_framesize(sensor.QQQVGA)
# You can set windowing to reduce the search image.
#sensor.set_windowing(((640-80)//2, (480-60)//2, 80, 60))
sensor.set_pixformat(sensor.GRAYSCALE)

# Load template.
# Template should be a small (eg. 32x32 pixels) grayscale image.
template = image.Image("/h.pgm")
templateu = image.Image("/u.pgm")
templates = image.Image("/s.pgm")

clock = time.clock()

# Run template matching
while (True):
    clock.tick()
    img = sensor.snapshot()
    pyb.LED(1).off()
    pyb.LED(2).off()
    pyb.LED(3).off()
    # find_template(template, threshold, [roi, step, search])
    # ROI: The region of interest tuple (x, y, w, h).
    # Step: The loop step used (y+=step, x+=step) use a bigger step to make it faster.
    # Search is either image.SEARCH_EX for exhaustive search or image.SEARCH_DS for diamond search
    #
    # Note1: ROI has to be smaller than the image and bigger than the template.
    # Note2: In diamond search, step and ROI are both ignored.
    h = img.find_template(template, 0.70, step=4, search=SEARCH_EX) #, roi=(10, 0, 60, 60))
    s = img.find_template(templates, 0.70, step=4, search=SEARCH_EX) #, roi=(10, 0, 60, 60))
    u = img.find_template(templateu, 0.70, step=4, search=SEARCH_EX) #, roi=(10, 0, 60, 60))

    if r:
        img.draw_rectangle(h)
        pyb.LED(1).on()#turn Led 1 on
        print("HHHHHHHHHHHHHHHH!!!")
    elif s:
        img.draw_rectangle(s)
        pyb.LED(3).on()#Turn led 3 on
        print("S!!!")
    elif u:
        img.draw_rectangle(u)
        pyb.LED(2).on()# Turn led 2 on
        print("u!!!")

    print(clock.fps())
