#include "common/common_utils/StrictMode.hpp"
STRICT_MODE_OFF
#ifndef RPCLIB_MSGPACK
#define RPCLIB_MSGPACK clmdep_msgpack
#endif // !RPCLIB_MSGPACK
#include "rpc/rpc_error.h"
STRICT_MODE_ON

#include "vehicles/multirotor/api/MultirotorRpcLibClient.hpp"
#include "common/common_utils/FileSystem.hpp"
#include <iostream>
#include <chrono>

int main(int argc, char *argv[]) 
{
    using namespace msr::airlib;

    msr::airlib::MultirotorRpcLibClient client;
    typedef ImageCaptureBase::ImageRequest ImageRequest;
    typedef ImageCaptureBase::ImageResponse ImageResponse;
    typedef ImageCaptureBase::ImageType ImageType;
    typedef common_utils::FileSystem FileSystem;
    
    try {
        client.confirmConnection();
        std::string vehicle_name = argv[1];

        client.enableApiControl(true, vehicle_name);
        client.armDisarm(true, vehicle_name);

        float takeoffTimeout = 5; 
        client.takeoffAsync(takeoffTimeout, vehicle_name)->waitOnLastTask();

        // switch to explicit hover mode so that this is the fall back when 
        // move* commands are finished.
        std::this_thread::sleep_for(std::chrono::duration<double>(5));
        client.hoverAsync(vehicle_name)->waitOnLastTask();

        // moveByVelocityZ is an offboard operation, so we need to set offboard mode.
        client.enableApiControl(true, vehicle_name); 
        auto position = client.getMultirotorState(vehicle_name).getPosition();
        float z = position.z(); // current position (NED coordinate system).  
        const float speed = 3.0f;
        const float size = 10.0f; 
        const float duration = size / speed;
        DrivetrainType driveTrain = DrivetrainType::ForwardOnly;
        YawMode yaw_mode(true, 0);
        std::cout << "moveByVelocityZ(" << speed << ", 0, " << z << "," << duration << ")" << std::endl;
        client.moveByVelocityZAsync(speed, 0, z, duration, driveTrain, yaw_mode, vehicle_name);
        std::this_thread::sleep_for(std::chrono::duration<double>(duration));
        std::cout << "moveByVelocityZ(0, " << speed << "," << z << "," << duration << ")" << std::endl;
        client.moveByVelocityZAsync(0, speed, z, duration, driveTrain, yaw_mode, vehicle_name);
        std::this_thread::sleep_for(std::chrono::duration<double>(duration));
        std::cout << "moveByVelocityZ(" << -speed << ", 0, " << z << "," << duration << ")" << std::endl;
        client.moveByVelocityZAsync(-speed, 0, z, duration, driveTrain, yaw_mode, vehicle_name);
        std::this_thread::sleep_for(std::chrono::duration<double>(duration));
        std::cout << "moveByVelocityZ(0, " << -speed << "," << z << "," << duration << ")" << std::endl;
        client.moveByVelocityZAsync(0, -speed, z, duration, driveTrain, yaw_mode, vehicle_name);
        std::this_thread::sleep_for(std::chrono::duration<double>(duration));

        client.hoverAsync(vehicle_name)->waitOnLastTask();

        client.landAsync(60.0F, vehicle_name)->waitOnLastTask();

        client.armDisarm(false, vehicle_name);

    }
    catch (rpc::rpc_error&  e) {
        std::string msg = e.get_error().as<std::string>();
        std::cout << "Exception raised by the API, something went wrong." << std::endl << msg << std::endl;
    }

    return 0;
}