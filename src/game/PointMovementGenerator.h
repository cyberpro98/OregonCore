/*
 * This file is part of the OregonCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OREGON_POINTMOVEMENTGENERATOR_H
#define OREGON_POINTMOVEMENTGENERATOR_H

#include "MovementGenerator.h"
#include "FollowerReference.h"

template<class T>
class PointMovementGenerator
    : public MovementGeneratorMedium< T, PointMovementGenerator<T> >
{
    public:
        PointMovementGenerator(uint32 _id, float _x, float _y, float _z, bool _usePathfinding) :
            i_x(_x), i_y(_y), i_z(_z), m_usePathfinding(_usePathfinding), id(_id) {}

        void Initialize(T&);
        void Finalize(T& unit);
        void Interrupt(T&);
        void Reset(T& unit)
        {
            unit.StopMoving();
        }
        bool Update(T&, const uint32& diff);

        void MovementInform(T&);

        MovementGeneratorType GetMovementGeneratorType()
        {
            return POINT_MOTION_TYPE;
        }
    private:
        float i_x, i_y, i_z;
        bool m_usePathfinding;
        uint32 id;
};

class AssistanceMovementGenerator
    : public PointMovementGenerator<Creature>
{
    public:
        AssistanceMovementGenerator(float _x, float _y, float _z) :
            PointMovementGenerator<Creature>(0, _x, _y, _z, true) {}

        MovementGeneratorType GetMovementGeneratorType()
        {
            return ASSISTANCE_MOTION_TYPE;
        }
        void Finalize(Creature&);
};

// Does almost nothing - just doesn't allows previous movegen interrupt current effect. Can be reused for charge effect
class EffectMovementGenerator : public MovementGenerator
{
    public:
        EffectMovementGenerator(uint32 Id) : m_Id(Id) {}
        void Initialize(Unit&) {}
        void Finalize(Unit&);
        void Interrupt(Unit&) {}
        void Reset(Unit&) {}
        bool Update(Unit&, const uint32&);
        MovementGeneratorType GetMovementGeneratorType() { return EFFECT_MOTION_TYPE; }
    private:
        uint32 m_Id;
};

#endif

