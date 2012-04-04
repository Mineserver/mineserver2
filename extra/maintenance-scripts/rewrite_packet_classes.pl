#!/usr/bin/perl

#int Mineserver::Network_Protocol_Notch_Packet_0xFE::read(packet_stream_t& ps, boost::shared_ptr<Mineserver::Network_Message_0xFE> message)
#{
#  ps >> message->mid;
#
#  if (ps.isValid()) {
#    ps.remove();
#    return STATE_MORE;
#  } else {
#    return STATE_NEEDMOREDATA;
#  }
#}

use strict;
use warnings;
use Data::Dumper qw(Dumper);

my $data = do { local $/; <STDIN> };
my $id = $ARGV[0];

my ($read_function) = ($data =~ /int Mineserver..Network_Protocol_Notch_Packet_0x....read\(.+?message\)\n\{\n(.+?)\n\}/igsm);
my ($write_function) = ($data =~ /void Mineserver..Network_Protocol_Notch_Packet_0x....write\(.+?ps\)\n\{(.+?)\n\}/igsm);

$read_function =~ s/\n\n  if \(ps.isValid.+$//s;
$read_function =~ s/message->/(*message)->/g;

$write_function =~ s/message->/message./g;

$read_function =~ s/^\s+//sg;
$read_function =~ s/\s+$//sg;
$write_function =~ s/^\s+//sg;
$write_function =~ s/\s+$//sg;

print <<HDR
/*
  Copyright (c) 2011-2012, The Mineserver Project
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  * Neither the name of the The Mineserver Project nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <mineserver/byteorder.h>
#include <mineserver/network/message/0x$id.h>
#include <mineserver/network/protocol/notch/packet.h>
#include <mineserver/network/protocol/notch/packet/0x$id.h>
HDR
;

print "\n";
print "int Mineserver::Network_Protocol_Notch_Packet_0x" . $id . "::_read(Mineserver::Network_Protocol_Notch_PacketStream& ps, Mineserver::Network_Message** message)\n";
print "{\n";
print "  *message = new Mineserver::Network_Message_0x" . $id . ";\n";
print "\n";
print "  " . $read_function . "\n";
print "\n";
print "  return STATE_GOOD;\n";
print "}\n";
print "\n";
print "int Mineserver::Network_Protocol_Notch_Packet_0x" . $id . "::_write(Mineserver::Network_Protocol_Notch_PacketStream& ps, const Mineserver::Network_Message& message)\n";
print "{\n";
print "  " . $write_function . "\n";
print "\n";
print "  return STATE_GOOD;\n";
print "}\n";
