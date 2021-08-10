#include <QWidget>

class AppQt : public QWidget
{
  Q_OBJECT // Very Important, this is all the magic that is needed
public:
  explicit AppQt(QWidget *parent = nullptr);

  // No need for a destructor (~HelloQt) here, the parent system makes sure that all the elements that
  // are parented to this is cleaned up

private slots:
  void writeToDebug();
};
