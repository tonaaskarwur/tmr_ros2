#include "rclcpp/rclcpp.hpp"
#include "tm_msgs/srv/ask_item.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;


int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);


  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("ask_item_node");
  rclcpp::Client<tm_msgs::srv::AskItem>::SharedPtr client =
    node->create_client<tm_msgs::srv::AskItem>("ask_item");
  auto request = std::make_shared<tm_msgs::srv::AskItem::Request>();
  request->id = "demo";
  request->item = "HandCamera_Value";
  request->wait_time = 0;
 
  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return false;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);
  // Wait for the result.
  if (rclcpp::spin_until_future_complete(node, result) ==
    rclcpp::executor::FutureReturnCode::SUCCESS)
  {
    //RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sum: %ld", result.get()->ok);
    if(result.get()->ok){
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"OK");
    } else{
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"not OK");
    }

  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service");
  }
  return true;
  

  rclcpp::shutdown();
  return 0;
}
