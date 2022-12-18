#include "Logger.h"
#include <QPushButton>

#include "config.h"

namespace logger {

Logger::Logger() {
  setWindowTitle("Вывод приложения");
  setFixedSize(config::SIZE_LOGGER);

  m_label = new QLabel();
  m_label->setWordWrap(true);
  m_label->setFont(config::MAIN_FONT);
  m_label->setAlignment(Qt::AlignTop | Qt::AlignLeft);

  m_vbox = new QVBoxLayout();
  m_vbox->addWidget(m_label);
  setLayout(m_vbox);

  show();
}

Logger::~Logger() {
  delete m_label;
  delete m_vbox;
}

void Logger::WriteLine(const QString& data) {
  m_label->setText(m_label->text() + data + "\n");
}

void Logger::Clear() {
  m_label->setText("");
}

}  // namespace logger