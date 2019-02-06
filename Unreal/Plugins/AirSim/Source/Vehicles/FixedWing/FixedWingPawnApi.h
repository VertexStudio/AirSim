#pragma once

#include "vehicles/fixedwing/api/FixedWingApiBase.hpp"
#include "WheeledVehicleMovementComponent4W.h"
#include "physics/Kinematics.hpp"
#include "FixedWingPawn.h"


class FixedWingPawnApi : public msr::airlib::FixedWingApiBase {
public:
    typedef msr::airlib::ImageCaptureBase ImageCaptureBase;

    FixedWingPawnApi(AFixedWingPawn* pawn, const msr::airlib::Kinematics::State* pawn_kinematics, const msr::airlib::GeoPoint& home_geopoint,
        const msr::airlib::AirSimSettings::VehicleSetting* vehicle_setting, std::shared_ptr<msr::airlib::SensorFactory> sensor_factory,
        const msr::airlib::Kinematics::State& state, const msr::airlib::Environment& environment);

    virtual void setFixedWingControls(const FixedWingApiBase::FixedWingControls& controls) override;

    virtual FixedWingApiBase::FixedWingState getFixedWingState() const override;

    virtual void reset() override;
    virtual void update() override;

    virtual msr::airlib::GeoPoint getHomeGeoPoint() const override;

    virtual void enableApiControl(bool is_enabled) override;
    virtual bool isApiControlEnabled() const override;
    virtual bool armDisarm(bool arm) override;

    virtual const FixedWingApiBase::FixedWingControls& getFixedWingControls() const override;

    virtual ~FixedWingPawnApi();

private:
    UWheeledVehicleMovementComponent* movement_;
    bool api_control_enabled_ = false;
    FixedWingControls last_controls_;
    AFixedWingPawn* pawn_;
    const msr::airlib::Kinematics::State* pawn_kinematics_;
    msr::airlib::GeoPoint  home_geopoint_;
};