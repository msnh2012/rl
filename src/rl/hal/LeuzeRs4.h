//
// Copyright (c) 2009, Markus Rickert
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

#ifndef RL_HAL_LEUZERS4_H
#define RL_HAL_LEUZERS4_H

#include <array>
#include <cstdint>

#include "CyclicDevice.h"
#include "Device.h"
#include "Lidar.h"
#include "Serial.h"

namespace rl
{
	namespace hal
	{
		/**
		 * Leuze RS4 safety laser scanner.
		 */
		class RL_HAL_EXPORT LeuzeRs4 : public CyclicDevice, public Lidar
		{
		public:
			enum class BaudRate
			{
				/** 4,800 bps. */
				b4800,
				/** 9,600 bps. */
				b9600,
				/** 19,200 bps. */
				b19200,
				/** 38,400 bps. */
				b38400,
				/** 57,600 bps. */
				b57600,
				/** 115,200 bps. */
				b115200,
				/** 345,600 bps. */
				b345600,
				/** 625,000 bps. */
				b625000
			};
			
			RL_HAL_DEPRECATED static constexpr BaudRate BAUDRATE_4800BPS = BaudRate::b4800;
			RL_HAL_DEPRECATED static constexpr BaudRate BAUDRATE_9600BPS = BaudRate::b9600;
			RL_HAL_DEPRECATED static constexpr BaudRate BAUDRATE_19200BPS = BaudRate::b19200;
			RL_HAL_DEPRECATED static constexpr BaudRate BAUDRATE_38400BPS = BaudRate::b38400;
			RL_HAL_DEPRECATED static constexpr BaudRate BAUDRATE_57600BPS = BaudRate::b57600;
			RL_HAL_DEPRECATED static constexpr BaudRate BAUDRATE_115200BPS = BaudRate::b115200;
			RL_HAL_DEPRECATED static constexpr BaudRate BAUDRATE_345600BPS = BaudRate::b345600;
			RL_HAL_DEPRECATED static constexpr BaudRate BAUDRATE_625000BPS = BaudRate::b625000;
			
			/**
			 * @param[in] password String with 8 characters.
			 */
			LeuzeRs4(
				const ::std::string& device = "/dev/ttyS0",
				const BaudRate& baudRate = BaudRate::b57600,
				const ::std::string& password = "ROD4LE"
			);
			
			virtual ~LeuzeRs4();
			
			void close();
			
			BaudRate getBaudRate() const;
			
			void getDistances(::rl::math::Vector& distances) const;
			
			::std::size_t getDistancesCount() const;
			
			::rl::math::Real getDistancesMaximum(const ::std::size_t& i) const;
			
			::rl::math::Real getDistancesMinimum(const ::std::size_t& i) const;
			
			::rl::math::Real getResolution() const;
			
			::rl::math::Real getStartAngle() const;
			
			::rl::math::Real getStopAngle() const;
			
			void open();
			
			void reset();
			
#if 0
			void setBaudRate(const BaudRate& baudRate);
			
			void setOutputParameters(const ::std::uint16_t& startIndex, const ::std::uint16_t& stopIndex, const ::std::uint16_t& step, const ::std::uint16_t& type);
#endif
			
			void start();
			
			void step();
			
			void stop();
			
		protected:
			
		private:
			::std::uint8_t crc(const ::std::uint8_t* buf, const ::std::size_t& len) const;
			
			const ::std::uint8_t& get(const ::std::uint8_t*& ptr) const;
			
			::std::size_t recv(uint8_t* buf, const ::std::size_t& len);
			
			void send(uint8_t* buf, const ::std::size_t& len);
			
			void set(const ::std::uint8_t& value, ::std::uint8_t*& ptr, ::std::size_t& len) const;
			
			BaudRate baudRate;
			
			::std::array<::std::uint8_t, 1099> data;
			
			BaudRate desired;
			
			bool far1;
			
			bool far2;
			
			bool fn1Fn2;
			
			bool near1;
			
			bool near2;
			
			::std::string password;
			
			Serial serial;
			
			::std::uint16_t startIndex;
			
			::std::uint16_t stepSize;
			
			::std::uint16_t stopIndex;
			
			::std::uint16_t type;
		};
	}
}

#endif // RL_HAL_LEUZERS4_H
