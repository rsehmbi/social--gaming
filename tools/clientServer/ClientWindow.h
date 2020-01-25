#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <functional>
#include <memory>


// Note: The ncurses state needs to be hidden from the public interface
// due to macro conflicts with boost asio. Thus, we hide the implementation
// requiring state behind indirection for a compilation firewall.
class ClientWindowImpl;


class ClientWindow {
public:
  explicit ClientWindow(std::function<void(std::string)> onTextEntry)
    : ClientWindow{std::move(onTextEntry), 1}
      { }

  ClientWindow(std::function<void(std::string)> onTextEntry, int updateDelay);
  
  ~ClientWindow();

  void update();

  void displayText(const std::string& text);

private:
  std::unique_ptr<ClientWindowImpl> impl;
};


#endif