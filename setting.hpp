#include <string>
template <typename T> class Setting {
private:
  T value;
  std::string label;

public:
  Setting(std::string label);
  Setting(std::string label, T v);
  T getValue();
  std::string getLabel();
  void setSetting(T v);
};
