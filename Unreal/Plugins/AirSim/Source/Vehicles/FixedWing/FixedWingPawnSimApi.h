#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicleMovementComponent4W.h"

#include "FixedWingPawn.h"
#include "FixedWingPawnApi.h"
#include "PawnEvents.h"
#include "PawnSimApi.h"
#include "vehicles/fixedwing/api/FixedWingApiBase.hpp"
#include "physics//Kinematics.hpp"
#include "common/Common.hpp"
#include "common/CommonStructs.hpp"

class FixedWingPawnSimApi : public PawnSimApi
{
public:
    typedef msr::airlib::Utils Utils;
    typedef msr::airlib::StateReporter StateReporter;
    typedef msr::airlib::UpdatableObject UpdatableObject;
    typedef msr::airlib::Pose Pose;
    
public:
    virtual void initialize() override;
    virtual ~FixedWingPawnSimApi() = default;

    //VehicleSimApiBase interface
    //implements game interface to update pawn
    FixedWingPawnSimApi(const Params& params,
        const FixedWingPawnApi::FixedWingControls&  keyboard_controls, UWheeledVehicleMovementComponent* movement);

    virtual void reset() override;
    virtual void update() override;

    virtual std::string getRecordFileLine(bool is_header_line) const override;

    virtual void updateRenderedState(float dt) override;
    virtual void updateRendering(float dt) override;

    msr::airlib::FixedWingApiBase* getVehicleApi() const
    {
        return vehicle_api_.get();
    }

    virtual msr::airlib::VehicleApiBase* getVehicleApiBase() const override
    {
        return vehicle_api_.get();
    }

private:
    void createVehicleApi(AFixedWingPawn* pawn, const msr::airlib::GeoPoint& home_geopoint);
    void updateFixedWingControls();

private:
    Params params_;

    std::unique_ptr<msr::airlib::FixedWingApiBase> vehicle_api_;
    std::vector<std::string> vehicle_api_messages_;

    //storing reference from pawn
    const FixedWingPawnApi::FixedWingControls& keyboard_controls_;

    FixedWingPawnApi::FixedWingControls joystick_controls_;
    FixedWingPawnApi::FixedWingControls current_controls_;
};
