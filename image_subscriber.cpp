#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
//added
#include <vector>
#include <string>
#include <unistd.h>
#include <array>
using namespace std;
class ImageSubscriberNode : public rclcpp::Node
{
public:
ImageSubscriberNode() : Node("image_subscriber_node")
{
// Open the serial port
serial_port_fd_ = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
if (serial_port_fd_ == -1)
{
RCLCPP_ERROR(this->get_logger(), "Failed to open serial port.");
return;
}
struct termios options;
tcgetattr(serial_port_fd_, &options);
cfsetispeed(&options, B9600);
cfsetospeed(&options, B9600);
options.c_cflag |= (CLOCAL | CREAD);
options.c_cflag &= ~PARENB;
options.c_cflag &= ~CSTOPB;
options.c_cflag &= ~CSIZE;
options.c_cflag |= CS8;
tcsetattr(serial_port_fd_, TCSANOW, &options);
// Subscribe to /image topic
subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
"/image_raw", 10,
[this](const sensor_msgs::msg::Image::SharedPtr msg) {
processImage(msg);
});
}
~ ImageSubscriberNode()
{
// Close the serial port
if (serial_port_fd_ != -1)
{
std::string cmd = "C 0 0\n";
write(serial_port_fd_, cmd.c_str(), cmd.length());
close(serial_port_fd_);
}
}
private:
void processImage(const sensor_msgs::msg::Image::SharedPtr msg)
{
if (count%15==0)
{
//Print some information about the received image message
//int red1 = msg->data[0];
RCLCPP_INFO(this->get_logger(), "Received image: width = %d, height = %d, encoding = %s",
msg->width, msg->height, msg->encoding.c_str());
// RCLCPP_INFO(this->get_logger(), "First Pixel Values: Red = %d, Green = %d, Blue = %d, Second Pixel value: Red = %d, Green = %d, Blue = %d",
//red1, msg->data[1], msg->data[2], msg->data[460800], msg->data[460801], msg->data[460802]);
// You can add further processing here based on your application's needs
int n;
int index;
int black_Z1=0;
int black_Z2=0;
int black_Z3=0;
int black_Z4=0;
int black_Z5=0;
// double total_pix=16384.00;
int Z_one=0;
int Z_two=0;
int Z_three=0;
int Z_four=0;
int Z_five=0;
// int startingRow=352;
int startingRow=240;
int endingRow=480;
int startingCol_Z1=3*0;
int endingCol_Z1=3*128;
int startingCol_Z2=endingCol_Z1;
int endingCol_Z2=256*3;
int startingCol_Z3=endingCol_Z2;
int endingCol_Z3=384*3;
int startingCol_Z4=endingCol_Z3;
int endingCol_Z4=512*3;
int startingCol_Z5=endingCol_Z4;
int endingCol_Z5=640*3;
for(n=startingRow;n<endingRow;n++)
{
for(index=startingCol_Z1+3*640*n;index<endingCol_Z1+3*640*n;index+=3)
{
int red = msg->data[index];
int green = msg->data[index+1];
int blue =msg->data[index+2];
// RCLCPP_INFO(this->get_logger(), "First Pixel Values: Red = %d, Green = %d, Blue = %d",
// msg->data[index], msg->data[index+1], msg->data[index+2]);
if((red<55) & (blue<55) & (green<55))
{
black_Z1=black_Z1+1;
}
}
}
for(n=startingRow;n<endingRow;n++)
{
for(index=startingCol_Z2+3*640*n;index<endingCol_Z2+3*640*n;index+=3)
{
int red = msg->data[index];
int green = msg->data[index+1];
int blue =msg->data[index+2];
// RCLCPP_INFO(this->get_logger(), "First Pixel ValuesZ2: Red = %d, Green = %d, Blue = %d",
// msg->data[index], msg->data[index+1], msg->data[index+2]);
if((red<55) & (blue<55) & (green<55))
{
black_Z2=black_Z2+1;
}
}
}
for(n=startingRow;n<endingRow;n++)
{
for(index=startingCol_Z3+3*640*n;index<endingCol_Z3+3*640*n;index+=3)
{
int red = msg->data[index];
int green = msg->data[index+1];
int blue =msg->data[index+2];
// RCLCPP_INFO(this->get_logger(), "First Pixel ValuesZ3: Red = %d, Green = %d, Blue = %d",
// msg->data[index], msg->data[index+1], msg->data[index+2]);
if((red<55) & (blue<55) & (green<55))
{
black_Z3=black_Z3+1;
}
}
}
for(n=startingRow;n<endingRow;n++)
{
for(index=startingCol_Z4+3*640*n;index<endingCol_Z4+3*640*n;index+=3)
{
int red = msg->data[index];
int green = msg->data[index+1];
int blue =msg->data[index+2];
// RCLCPP_INFO(this->get_logger(), "First Pixel ValuesZ4: Red = %d, Green = %d, Blue = %d",
// msg->data[index], msg->data[index+1], msg->data[index+2]);
if((red<55) & (blue<55) & (green<55))
{
black_Z4=black_Z4+1;
}
}
}
for(n=startingRow;n<endingRow;n++)
{
for(index=startingCol_Z5+3*640*n;index<endingCol_Z5+3*640*n;index+=3)
{
int red = msg->data[index];
int green = msg->data[index+1];
int blue =msg->data[index+2];
// RCLCPP_INFO(this->get_logger(), "First Pixel ValuesZ5: Red = %d, Green = %d, Blue = %d",
// msg->data[index], msg->data[index+1], msg->data[index+2]);
if((red<55) & (blue<55) & (green<55))
{
black_Z5=black_Z5+1;
}
}
}
//double percent_black_Z1=(black_Z1*100.00)/(total_pix);
//RCLCPP_INFO(this->get_logger(), "Zone 1 is black_Z1 = %d Percent Black",
// msg->black_Z1);
RCLCPP_INFO(this->get_logger(), "percent black is = %d Percent Black",
black_Z1);
RCLCPP_INFO(this->get_logger(), "Z2percent black is = %d Percent Black",
black_Z2);
RCLCPP_INFO(this->get_logger(), "Z3percent black is = %d Percent Black",
black_Z3);
RCLCPP_INFO(this->get_logger(), "Z4percent black is = %d Percent Black",
black_Z4);
RCLCPP_INFO(this->get_logger(), "Z5percent black is = %d Percent Black",
black_Z5);
if (black_Z1 > 5500)
Z_one=1;
if (black_Z2 > 5500)
Z_two=1;
if (black_Z3 > 5500)
Z_three=1;
if (black_Z4 > 5500)
Z_four=1;
if (black_Z5 > 5500)
Z_five=1;
//forwards
if (Z_one==0 && Z_two==0 && Z_three==1 && Z_four==0 && Z_five==0){
std::string cmd = "C 1 1\n";
write(serial_port_fd_, cmd.c_str(), cmd.length());
RCLCPP_INFO(this->get_logger(), "%s",cmd.c_str());
}
else if (Z_one==0 && Z_two==1 && Z_three==1 && Z_four==1 &&
Z_five==0){
std::string cmd = "C 1 1\n";
write(serial_port_fd_, cmd.c_str(), cmd.length());
RCLCPP_INFO(this->get_logger(), "%s",cmd.c_str());
}
else if (Z_one==1 && Z_two==0 && Z_three==1 && Z_four==0 &&
Z_five==1){
std::string cmd = "C 1 1\n";
write(serial_port_fd_, cmd.c_str(), cmd.length());
RCLCPP_INFO(this->get_logger(), "%s",cmd.c_str());
}
else if (Z_one==1 && Z_two==1 && Z_three==1 && Z_four==1 &&
Z_five==1){
std::string cmd = "C 1 1\n";
write(serial_port_fd_, cmd.c_str(), cmd.length());
RCLCPP_INFO(this->get_logger(), "%s",cmd.c_str());
}
//left
else if (Z_one==0 && Z_two==1 && Z_three==0 && Z_four==0 &&
Z_five==0){
std::string cmd = "C -0.25 0.25\n";
write(serial_port_fd_, cmd.c_str(), cmd.length());
RCLCPP_INFO(this->get_logger(), "%s",cmd.c_str());
}
else if (Z_one==1 && Z_two==1 && Z_three==0 && Z_four==0 &&
Z_five==0){
std::string cmd = "C -0.25 0.25\n";
write(serial_port_fd_, cmd.c_str(), cmd.length());
RCLCPP_INFO(this->get_logger(), "%s",cmd.c_str());
}
else if (Z_one==0 && Z_two==1 && Z_three==1 && Z_four==0 &&
Z_five==0){
std::string cmd = "C -0.25 0.25\n";
write(serial_port_fd_, cmd.c_str(), cmd.length());
RCLCPP_INFO(this->get_logger(), "%s",cmd.c_str());
}
else if (Z_one==1 && Z_two==1 && Z_three==1 && Z_four==0 &&
Z_five==0){
std::string cmd = "C -0.25 0.25\n";
write(serial_port_fd_, cmd.c_str(), cmd.length());
RCLCPP_INFO(this->get_logger(), "%s",cmd.c_str());
}
else if (Z_one==1 && Z_two==1 && Z_three==1 && Z_four==1 &&
Z_five==0){
std::string cmd = "C -0.25 0.25\n";
write(serial_port_fd_, cmd.c_str(), cmd.length());
RCLCPP_INFO(this->get_logger(), "%s",cmd.c_str());
}
//right
else if (Z_one==0 && Z_two==0 && Z_three==0 && Z_four==1 &&
Z_five==0){
std::string cmd = "C 0.25 -0.25\n";
write(serial_port_fd_, cmd.c_str(), cmd.length());
RCLCPP_INFO(this->get_logger(), "%s",cmd.c_str());
}
else if (Z_one==0 && Z_two==0 && Z_three==0 && Z_four==1 &&
Z_five==1){
std::string cmd = "C 0.25 -0.25\n";
write(serial_port_fd_, cmd.c_str(), cmd.length());
RCLCPP_INFO(this->get_logger(), "%s",cmd.c_str());
}
else if (Z_one==0 && Z_two==0 && Z_three==1 && Z_four==1 &&
Z_five==0){
std::string cmd = "C 0.25 -0.25\n";
write(serial_port_fd_, cmd.c_str(), cmd.length());
RCLCPP_INFO(this->get_logger(), "%s",cmd.c_str());
}
else if (Z_one==0 && Z_two==0 && Z_three==1 && Z_four==1 &&
Z_five==1){
std::string cmd = "C 0.25 -0.25\n";
write(serial_port_fd_, cmd.c_str(), cmd.length());
RCLCPP_INFO(this->get_logger(), "%s",cmd.c_str());
}
else if (Z_one==0 && Z_two==1 && Z_three==1 && Z_four==1 &&
Z_five==1){
std::string cmd = "C 0.25 -0.25\n";
write(serial_port_fd_, cmd.c_str(), cmd.length());
RCLCPP_INFO(this->get_logger(), "%s",cmd.c_str());
}
//stop
else if (Z_one==0 && Z_two==0 && Z_three==0 && Z_four==0 &&
Z_five==0){
std::string cmd = "C 0 0\n";
write(serial_port_fd_, cmd.c_str(), cmd.length());
RCLCPP_INFO(this->get_logger(), "%s",cmd.c_str());
}
else {
std::string cmd = "C -0.25 -0.35\n";
write(serial_port_fd_, cmd.c_str(), cmd.length());
}
RCLCPP_INFO(this->get_logger(), "Z1 is = %d",
Z_one);
RCLCPP_INFO(this->get_logger(), "Z2 is= %d",
Z_two);
RCLCPP_INFO(this->get_logger(), "Z3 is = %d",
Z_three);
RCLCPP_INFO(this->get_logger(), "Z4 is = %d",
Z_four);
RCLCPP_INFO(this->get_logger(), "Z5 is = %d",
Z_five);
// std::string cmd = "C 1 1";
// write(serial_port_fd_, cmd.c_str(), cmd.length());
// RCLCPP_INFO(this->get_logger(), "%s",cmd.c_str());
}
count++;
}
rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
int serial_port_fd_;
unsigned long int count=0;
};
int main(int argc, char * argv[])
{
rclcpp::init(argc, argv);
rclcpp::spin(std::make_shared<ImageSubscriberNode>());
rclcpp::shutdown();
return 0;
}
