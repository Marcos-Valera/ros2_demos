#include "rclcpp/rclcpp.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include "std_msgs/msg/string.hpp"
#include "demo_nodes_cpp/visibility_control.h"

using namespace std::chrono_literals;

namespace demo_nodes_cpp
{
class NumberProcessor : public rclcpp::Node
{
public:
  DEMO_NODES_CPP_PUBLIC
  explicit NumberProcessor(const rclcpp::NodeOptions & options)
  : Node("number_processor", options)
  {
    auto callback =
      [this](std_msgs::msg::String::ConstSharedPtr msg) -> void
      {
      	int x = std::stoi(msg->data);
      	int y = x * x;
      	
        RCLCPP_INFO(this->get_logger(), "%d^2 = %d", x, y);
        
        auto out_msg = std::make_unique<std_msgs::msg::String>();
        out_msg->data = std::to_string(y);
        
        pub_->publish(std::move(out_msg));
      };
    rclcpp::QoS qos(rclcpp::KeepLast{7});
    pub_ = this->create_publisher<std_msgs::msg::String>("processed_data", qos);
    sub_ = create_subscription<std_msgs::msg::String>("chatter", 10, callback);
  }

private:
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
};

}  // namespace demo_nodes_cpp

RCLCPP_COMPONENTS_REGISTER_NODE(demo_nodes_cpp::NumberProcessor)
