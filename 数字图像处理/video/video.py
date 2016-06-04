# coding=utf-8
import cv2
cap = cv2.VideoCapture("green.mp4")
fgbg = cv2.BackgroundSubtractorMOG()
new_bg = cv2.imread("bg.jpg")

# 获取视频文件的大小
size = (int(cap.get(cv2.cv.CV_CAP_PROP_FRAME_WIDTH)),int(cap.get(cv2.cv.CV_CAP_PROP_FRAME_HEIGHT)))
# 改变背景图片的大小与视频文件一致
new_bg = cv2.resize(new_bg, size, interpolation = cv2.INTER_CUBIC)

# 保存视频的视频流
fps = int(cap.get(cv2.cv.CV_CAP_PROP_FPS))
codec = int(cap.get(cv2.cv.CV_CAP_PROP_FOURCC))
videoWriter = cv2.VideoWriter('result.mp4', cv2.cv.CV_FOURCC('m','p','4','v'), fps, size)

ret = True
while ret:
    ret, src = cap.read()
    fgmask = fgbg.apply(src, learningRate=0)
    dst = src.copy()
    dst = cv2.bitwise_and(dst, src, mask=fgmask)
    dst = cv2.addWeighted(dst,0.6,new_bg,0.4,0)

    # 显示合成后的结果
    cv2.imshow('frame',dst)

    #写视频帧
    videoWriter.write(dst)

    k = cv2.waitKey(30) & 0xff
    if k == 27:  # ESC key
        break
cap.release()
cv2.destroyAllWindows()
