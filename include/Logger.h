#ifndef SMO_LOGGER_H
#define SMO_LOGGER_H

#include <QLabel>
#include <QMainWindow>
#include <QVBoxLayout>

namespace logger {

class Logger : public QWidget {
  Q_OBJECT
 public:
  explicit Logger();
  ~Logger() override;

  void WriteLine(const QString& data);
  void Clear();

 private:
  QLabel* m_label;
  QVBoxLayout* m_vbox;
};

}  // namespace logger

#endif  //SMO_LOGGER_H
