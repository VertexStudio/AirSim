// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#ifndef air_FixedWingRpcLibClient_hpp
#define air_FixedWingRpcLibClient_hpp

#include "common/Common.hpp"
#include <functional>
#include "common/CommonStructs.hpp"
#include "vehicles/fixedwing/api/FixedWingApiBase.hpp"
#include "api/RpcLibClientBase.hpp"
#include "common/ImageCaptureBase.hpp"


namespace msr { namespace airlib {

class FixedWingRpcLibClient : public RpcLibClientBase {
public:
    FixedWingRpcLibClient(const string& ip_address = "localhost", uint16_t port = 41451, float timeout_sec = 60);

    void setFixedWingControls(const FixedWingApiBase::FixedWingControls& controls, const std::string& vehicle_name = "");
    FixedWingApiBase::FixedWingState getFixedWingState(const std::string& vehicle_name = "");

    virtual ~FixedWingRpcLibClient();    //required for pimpl
};

}} //namespace
#endif
