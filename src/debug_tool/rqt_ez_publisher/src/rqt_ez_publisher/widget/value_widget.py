from python_qt_binding import QtGui
from python_qt_binding import QtWidgets
from python_qt_binding.QtWidgets import QWidget
from . import base_widget
from .. import ez_publisher_model as ez_model


class ValueWidget(base_widget.BaseWidget):

    def __init__(self, topic_name, attributes, array_index, publisher, parent,
                 label_text=None):
        super(ValueWidget, self).__init__(topic_name, publisher, parent=parent)
        self._parent = parent
        self._attributes = attributes
        self._array_index = array_index
        self._text = ez_model.make_text(topic_name, attributes, array_index)
        self._horizontal_layout = QtWidgets.QHBoxLayout()
        if label_text is None:
            self._topic_label = QtWidgets.QLabel(self._text)
        else:
            self._topic_label = QtWidgets.QLabel(label_text)
        self.close_button = QtWidgets.QPushButton()
        self.close_button.setMaximumWidth(30)
        self.close_button.setIcon(
            self.style().standardIcon(QtWidgets.QStyle.SP_TitleBarCloseButton))
        self.up_button = QtWidgets.QPushButton()
        self.up_button.setIcon(
            self.style().standardIcon(QtWidgets.QStyle.SP_ArrowUp))
        self.up_button.setMaximumWidth(30)
        self.down_button = QtWidgets.QPushButton()
        self.down_button.setMaximumWidth(30)
        self.down_button.setIcon(
            self.style().standardIcon(QtWidgets.QStyle.SP_ArrowDown))
        repeat_label = QtWidgets.QLabel('repeat')
        self._repeat_box = QtWidgets.QCheckBox()
        self._repeat_box.stateChanged.connect(self.repeat_changed)
        self._repeat_box.setChecked(publisher.is_repeating())
        self._publish_button = QtWidgets.QPushButton('Publish')
        self._publish_button.clicked.connect(publisher.publish)
        self._horizontal_layout.addWidget(self._topic_label)
        self._horizontal_layout.addWidget(self.close_button)
        self._horizontal_layout.addWidget(self.up_button)
        self._horizontal_layout.addWidget(self.down_button)
        if self._array_index is not None:
            self.add_button = QtWidgets.QPushButton('+')
            self.add_button.setMaximumWidth(30)
            self._horizontal_layout.addWidget(self.add_button)
        else:
            self.add_button = None
        self.close_button.clicked.connect(
            lambda x: self._parent.close_slider(self))
        self.up_button.clicked.connect(
            lambda x: self._parent.move_up_widget(self))
        self.down_button.clicked.connect(
            lambda x: self._parent.move_down_widget(self))
        self.setup_ui(self._text)
        self._horizontal_layout.addWidget(self._publish_button)
        self._horizontal_layout.addWidget(repeat_label)
        self._horizontal_layout.addWidget(self._repeat_box)

    def repeat_changed(self, state):
        self.set_is_repeat(state == 2)

    def update(self):
        self._repeat_box.setChecked(self.is_repeat())

    def get_text(self):
        return self._text

    def publish_value(self, value):
        ez_model.set_msg_attribute_value(self._publisher.get_message(),
                                         self._topic_name, self._type, self._attributes,
                                         self._array_index, value)
        self._publisher.publish()

    def setup_ui(self, name):
        pass

    def get_range(self):
        return (0, 0)

    def set_range(self, range):
        pass

    def set_configurable(self, value):
        self.down_button.setVisible(value)
        self.up_button.setVisible(value)
        self.close_button.setVisible(value)
        if self.add_button:
            self.add_button.setVisible(value)
