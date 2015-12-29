import cv2
import numpy as np



img = cv2.imread('./images/G0040264.JPG')
retval, threshold = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)
#review image window imshow default size
#Get's rid of giant unmanageable windows for high resolution images
# http://stackoverflow.com/questions/19285562/python-opencv-imread-displaying-image
screen_res = 1280, 720
scale_width = screen_res[0] / img.shape[1]
scale_height = screen_res[1] / img.shape[0]
scale = min(scale_width, scale_height)
window_width = int(img.shape[1] * scale)
window_height = int(img.shape[0] * scale)

cv2.namedWindow('review', cv2.WINDOW_NORMAL)
cv2.resizeWindow('review', window_width, window_height)

cv2.imshow('review',img)
cv2.imshow('thresh',threshold)
cv2.waitKey(0)
cv2.destroyAllWindows()
