import cv2
import numpy as np


def main():
    img = cv2.imread('./images/G0040264.JPG')
    retval, threshold = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)
    scale_width, scale_height = scale(img)

    previewWindow('test1', img, scale_width, scale_height)
    previewWindow('threshold', threshold, scale_width, scale_height)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


def previewWindow(name, img, scale_width, scale_height):
    cv2.namedWindow(name, cv2.WINDOW_NORMAL)
    cv2.resizeWindow(name, scale_width, scale_height)
    resized = cv2.resize(img, (img.shape[1]/scale_width, img.shape[0]/scale_height), interpolation = cv2.INTER_AREA)
    cv2.imshow(name, resized)
    return

    # review image window imshow default size
    # Get's rid of giant unmanageable windows for high resolution images
    # http://stackoverflow.com/questions/19285562/python-opencv-imread-displaying-image
    # had to rework the logic of the answer 1280/4000 is 0
    # probably integer vs float
    # this rescales to nearest integer of resolution

def scale(img, scr_height=1280, scr_width=729):
    screen_res = scr_height, scr_width
    scale_width = img.shape[1] / screen_res[0]
    scale_height = img.shape[0] /  screen_res[1]

    print "sh: " , scale_height , " sw: " , scale_width
    return  scale_width, scale_height


if __name__ == '__main__':
  main()



