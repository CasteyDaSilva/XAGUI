LOCAL_PATH := $(call my-dir)/../../src

include $(CLEAR_VARS)

LOCAL_MODULE := libXAGUI

LOCAL_SRC_FILES += \
    XML/tinyxml2.cpp \
    AnalogStick.cpp \
    Button.cpp \
	CheckBox.cpp \
	Control.cpp \
	ControlBase.cpp \
    Font.cpp \
    Form.cpp \
	Label.cpp \
    MultilineTextBox.cpp \
    PasswordTextBox.cpp \
	PictureBox.cpp \
    ProggressBar.cpp \
	RadioButton.cpp \
	Renderer.cpp \
    Slider.cpp \
    StaticText.cpp \
	TextBox.cpp \
    Texture.cpp \
    Window.cpp \
	XAGUI.cpp

LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../include/

include $(BUILD_STATIC_LIBRARY)