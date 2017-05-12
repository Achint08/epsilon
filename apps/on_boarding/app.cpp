#include "app.h"

namespace OnBoarding {

App::App(Container * container, UpdateController * updateController) :
  ::App(container, &m_languageController),
  m_languageController(&m_modalViewController, &m_logoController, updateController),
  m_logoController()
{
}

void App::reinitOnBoarding() {
  m_languageController.reinitOnBoarding();
}

bool App::hasTimer() {
  return firstResponder() == &m_logoController;
}

Timer * App::timer() {
  return &m_logoController;
}

}