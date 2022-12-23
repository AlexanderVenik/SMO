#ifndef SMO_INPUTFIELD_H
#define SMO_INPUTFIELD_H

#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>

namespace field {

class InputField : public QWidget {
  Q_OBJECT
 public:
  explicit InputField(const QString& caption);
  ~InputField() override;

  QFormLayout* GetLayout() const;
  QString GetText() const;
  void SetText(const QString& data) const;

 private:
  QFormLayout* m_layout;
  QLineEdit* m_field;
};

}  // namespace field

#endif  //SMO_INPUTFIELD_H
