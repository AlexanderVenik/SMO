#include "InputField.h"
#include "config.h"

field::InputField::InputField(const QString& caption) {
  m_field = new QLineEdit();
  m_field->setFont(config::MAIN_FONT);

  m_layout = new QFormLayout();
  m_layout->addRow(caption, m_field);
}

field::InputField::~InputField() {
  delete m_field;
  delete m_layout;
}

QFormLayout* field::InputField::GetLayout() const {
  return m_layout;
}

QString field::InputField::GetText() const {
  return m_field->text();
}

void field::InputField::SetText(const QString& data) const {
  m_field->setText(data);
}
