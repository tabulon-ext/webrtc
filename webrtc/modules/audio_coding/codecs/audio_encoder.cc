/*
 *  Copyright (c) 2014 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "webrtc/modules/audio_coding/codecs/audio_encoder.h"

#include "webrtc/base/checks.h"
#include "webrtc/base/trace_event.h"

namespace webrtc {

AudioEncoder::EncodedInfo::EncodedInfo() = default;
AudioEncoder::EncodedInfo::EncodedInfo(const EncodedInfo&) = default;
AudioEncoder::EncodedInfo::EncodedInfo(EncodedInfo&&) = default;
AudioEncoder::EncodedInfo::~EncodedInfo() = default;
AudioEncoder::EncodedInfo& AudioEncoder::EncodedInfo::operator=(
    const EncodedInfo&) = default;
AudioEncoder::EncodedInfo& AudioEncoder::EncodedInfo::operator=(EncodedInfo&&) =
    default;

int AudioEncoder::RtpTimestampRateHz() const {
  return SampleRateHz();
}

AudioEncoder::EncodedInfo AudioEncoder::Encode(
    uint32_t rtp_timestamp,
    rtc::ArrayView<const int16_t> audio,
    rtc::Buffer* encoded) {
  TRACE_EVENT0("webrtc", "AudioEncoder::Encode");
  RTC_CHECK_EQ(audio.size(),
               static_cast<size_t>(NumChannels() * SampleRateHz() / 100));

  const size_t old_size = encoded->size();
  EncodedInfo info = EncodeImpl(rtp_timestamp, audio, encoded);
  RTC_CHECK_EQ(encoded->size() - old_size, info.encoded_bytes);
  return info;
}

bool AudioEncoder::SetFec(bool enable) {
  return !enable;
}

bool AudioEncoder::SetDtx(bool enable) {
  return !enable;
}

bool AudioEncoder::GetDtx() const {
  return false;
}

bool AudioEncoder::SetApplication(Application application) {
  return false;
}

void AudioEncoder::SetMaxPlaybackRate(int frequency_hz) {}

void AudioEncoder::SetTargetBitrate(int target_bps) {}

rtc::ArrayView<std::unique_ptr<AudioEncoder>>
AudioEncoder::ReclaimContainedEncoders() { return nullptr; }

bool AudioEncoder::EnableAudioNetworkAdaptor(const std::string& config_string,
                                             const Clock* clock) {
  return false;
}

void AudioEncoder::DisableAudioNetworkAdaptor() {}

void AudioEncoder::OnReceivedUplinkBandwidth(int uplink_bandwidth_bps) {}

void AudioEncoder::OnReceivedUplinkPacketLossFraction(
    float uplink_packet_loss_fraction) {}

void AudioEncoder::OnReceivedTargetAudioBitrate(int target_audio_bitrate_bps) {}

void AudioEncoder::OnReceivedRtt(int rtt_ms) {}

void AudioEncoder::OnReceivedOverhead(size_t overhead_bytes_per_packet) {}

void AudioEncoder::SetReceiverFrameLengthRange(int min_frame_length_ms,
                                               int max_frame_length_ms) {}

}  // namespace webrtc
