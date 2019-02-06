// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

//in header only mode, control library is not available
#ifndef AIRLIB_HEADER_ONLY
//RPC code requires C++14. If build system like Unreal doesn't support it then use compiled binaries
#ifndef AIRLIB_NO_RPC
//if using Unreal Build system then include precompiled header file first

#include "vehicles/fixedwing/api/FixedwingRpcLibServer.hpp"


#include "common/Common.hpp"
STRICT_MODE_OFF

#ifndef RPCLIB_MSGPACK
#define RPCLIB_MSGPACK clmdep_msgpack
#endif // !RPCLIB_MSGPACK
#include "common/common_utils/MinWinDefines.hpp"
#undef NOUSER

#include "common/common_utils/WindowsApisCommonPre.hpp"
#undef FLOAT
#undef check
#include "rpc/server.h"
//TODO: HACK: UE4 defines macro with stupid names like "check" that conflicts with msgpack library
#ifndef check
#define check(expr) (static_cast<void>((expr)))
#endif
#include "common/common_utils/WindowsApisCommonPost.hpp"

#include "vehicles/fixedwing/api/FixedwingRpcLibAdapators.hpp"


STRICT_MODE_ON


namespace msr { namespace airlib {

typedef msr::airlib_rpclib::FixedwingRpcLibAdapators FixedwingRpcLibAdapators;

FixedwingRpcLibServer::FixedwingRpcLibServer(ApiProvider* api_provider, string server_address, uint16_t port)
    : RpcLibServerBase(api_provider, server_address, port)
{
    (static_cast<rpc::server*>(getServer()))->
        bind("getFixedwingState", [&](const std::string& vehicle_name) -> FixedwingRpcLibAdapators::FixedwingState {
        return FixedwingRpcLibAdapators::FixedwingState(getVehicleApi(vehicle_name)->getFixedwingState());
    });

    (static_cast<rpc::server*>(getServer()))->
        bind("setFixedwingControls", [&](const FixedwingRpcLibAdapators::FixedwingControls& controls, const std::string& vehicle_name) -> void {
        getVehicleApi(vehicle_name)->setFixedwingControls(controls.to());
    });

}

//required for pimpl
FixedwingRpcLibServer::~FixedwingRpcLibServer()
{
}

}} //namespace


#endif
#endif
