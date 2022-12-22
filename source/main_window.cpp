#include "main_window.h"
#include "common.h"
#include "config.h"
#include "types.h"

#include <QLabel>
#include <QWindow>
#include <array>

MainWindow::MainWindow(QWidget* parent) {
  setWindowTitle("Системы массового обслуживания");
  m_vbox = new QVBoxLayout();

  m_lambda_input = new field::InputField(tr("Заявок в минуту"));
  m_time_input = new field::InputField(tr("Время обработки"));
  m_count_stream = new field::InputField(tr("Кол-во потоков"));
  m_queue_size = new field::InputField(tr("Размер очереди"));

#ifdef QT_DEBUG
//  m_lambda_input->SetText("1.9");
//  m_time_input->SetText("2.1");
//  m_count_stream->SetText("4");
#endif

  m_btn_decision = new QPushButton("Решить");

  m_vbox->addLayout(m_lambda_input->GetLayout());
  m_vbox->addLayout(m_time_input->GetLayout());
  m_vbox->addLayout(m_count_stream->GetLayout());
//  m_vbox->addLayout(m_queue_size->GetLayout());
  m_vbox->addWidget(m_btn_decision);
  setLayout(m_vbox);

  m_logger = new logger::Logger();
  // connects
  connect(m_btn_decision, SIGNAL(clicked(bool)),
          this, SLOT(StartDecision()));
  // all show
  show();
}

MainWindow::~MainWindow() {
  delete m_vbox;
  delete m_lambda_input;
  delete m_time_input;
  delete m_count_stream;
  delete m_logger;
}

void MainWindow::StartDecision() {
  m_logger->Clear();

  auto lambda_data = m_lambda_input->GetText();
  auto time_data = m_time_input->GetText();
  auto count_stream_data = m_count_stream->GetText();
  auto queue_size = m_queue_size->GetText();

  m_logger->WriteLine("lambda = " + lambda_data);
  m_logger->WriteLine("time of processing = " + time_data);
  m_logger->WriteLine("count stream = " + count_stream_data);

  f64 lambda = lambda_data.toFloat();
  f64 time = time_data.toFloat();
  u8 count_stream = count_stream_data.toUInt();

  f64 u = 1 / time;
  m_logger->WriteLine("u (интенсивность потока обслуживания) = " +
                      QString::number(u));

  f64 p = lambda * time;
  m_logger->WriteLine("p (коэффициент загрузки системы) = " +
                      QString::number(p));

  f64 temp_p0 = 0;
  for (u8 idx_stream = 1; idx_stream <= count_stream; ++idx_stream) {
    temp_p0 += std::pow(p, idx_stream) / math::factorial(idx_stream);
  }

  f64 p0 = 1 / (1 + temp_p0);
  m_logger->WriteLine("p0 = " + QString::number(p0));

  f64 p_n[count_stream];
  f64 sun_pn = 0.0;
  for (u8 idx_stream = 0; idx_stream < count_stream; ++idx_stream) {
    p_n[idx_stream] =
        (p0 * std::pow(p, idx_stream + 1)) / math::factorial(idx_stream + 1);
    sun_pn += p_n[idx_stream];

    m_logger->WriteLine("p" + QString::number(idx_stream + 1) + " = " +
                        QString::number(p_n[idx_stream]));
  }

  m_logger->WriteLine("Сумма pn = " + QString::number(sun_pn));

  m_logger->WriteLine("Вероятность отказа = " +
                      QString::number(p_n[count_stream - 1] * 100) + "%");

  f64 q = 1 - p_n[count_stream - 1];
  m_logger->WriteLine("Относительная пропускная способность = " +
                      QString::number(q));

  f64 a = q * lambda;
  m_logger->WriteLine("Абсолютная пропускная способность = " +
                      QString::number(a));

  f64 k = a / u;
  m_logger->WriteLine("Среднее число занятых линий связи = " +
                      QString::number(k));

  f64 t_sist = k / lambda;
  m_logger->WriteLine("В системе заявка в среднем находится = " +
                      QString::number(t_sist) + " мин.");

  m_logger->WriteLine(
      "Высокой вероятности отказа, загруженность АТС составляет около " +
      QString::number(k / count_stream * 100) + "% линий связи");


}
