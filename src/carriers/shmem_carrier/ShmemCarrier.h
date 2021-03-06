/*
 * Copyright (C) 2006-2019 Istituto Italiano di Tecnologia (IIT)
 * Copyright (C) 2006-2010 RobotCub Consortium
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef YARP_SHMEM_SHMEMCARRIER_H
#define YARP_SHMEM_SHMEMCARRIER_H

#include <yarp/os/AbstractCarrier.h>


/**
 * Communicating between two ports via shared memory.
 */
class ShmemCarrier : public yarp::os::AbstractCarrier
{
public:
    ShmemCarrier();
    virtual ~ShmemCarrier();

    Carrier* create() const override;

    std::string getName() const override;

    virtual int getSpecifierCode() const;
    bool requireAck() const override;
    bool isConnectionless() const override;
    bool checkHeader(const yarp::os::Bytes& header) override;
    void getHeader(yarp::os::Bytes& header) const override;
    void setParameters(const yarp::os::Bytes& header) override;
    bool respondToHeader(yarp::os::ConnectionState& proto) override;
    bool expectReplyToHeader(yarp::os::ConnectionState& proto) override;

private:
    bool becomeShmemVersionHybridStream(yarp::os::ConnectionState& proto, bool sender);
    bool becomeShmem(yarp::os::ConnectionState& proto, bool sender);
};

#endif // YARP_SHMEM_SHMEMCARRIER_H
