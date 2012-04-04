#!/usr/bin/perl -w

use strict;
use warnings;
use Data::Dumper qw(Dumper);

my $license = <<LIC
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
LIC
;

my $data = do { local $/; <>; };

my @classes = ($data =~ /(  struct Network_Protocol_Notch_Packet_(?:Client|Server)_0x(?:[0-9A-F]+).+?\};\n)/isgm);

foreach my $class (@classes) {
  my ($id) = ($class =~ /_0x([0-9A-F]+)/);

  $class =~ s/  public:\n//sg;
  $class =~ s/_(Client|Server)_/_/g;

  my $head = $class;
  my $impl = $class;

  my $fh;

  $head =~ s/(    void .+?)\n\s+\{.+?\}\n/$1;\n/sg;
#  $head =~ s/Network_Protocol_Notch_/Network_/g;
  $head =~ s/    void/\n    void/;

  open $fh, ">0x" . $id . ".h";

  syswrite $fh, "$license";
  syswrite $fh, "\n";
  syswrite $fh, "#ifndef _MINESERVER_NETWORK_PROTOCOL_NOTCH_PACKET_0x" . $id . "_H\n";
  syswrite $fh, "#define _MINESERVER_NETWORK_PROTOCOL_NOTCH_PACKET_0x" . $id . "_H\n";
  syswrite $fh, "\n";
  syswrite $fh, "#include <mineserver/byteorder.h>\n";
  syswrite $fh, "#include <mineserver/network/packet.h>\n";
  syswrite $fh, "\n";
  syswrite $fh, "namespace Mineserver\n";
  syswrite $fh, "{\n";
  syswrite $fh, $head;
  syswrite $fh, "};\n";
  syswrite $fh, "\n";
  syswrite $fh, "#endif";

  close $fh;

  $impl =~ s/^  struct Network_Protocol_Notch_Packet_0x(?:[0-9A-F]+).+?\n  {(.+?)};\n$/$1/isg;
  $impl =~ s/void /\nvoid Mineserver::Network_Protocol_Notch_Packet_0x${id}::/g;
  $impl =~ s/^    //igm;
  $impl =~ s/^[^{]+;\n//isg;
  $impl =~ s/^\s+//sg;
  $impl =~ s/\s+$//sg;

  open $fh, ">0x" . $id . ".cpp";

  syswrite $fh, "$license";
  syswrite $fh, "\n";
  syswrite $fh, "#include <mineserver/byteorder.h>\n";
  syswrite $fh, "#include <mineserver/network/packet.h>\n";
  syswrite $fh, "#include <mineserver/network/protocol/notch/packetstream.h>\n";
  syswrite $fh, "#include <mineserver/network/protocol/notch/packet.h>\n";
  syswrite $fh, "#include <mineserver/network/protocol/notch/packet/0x" . $id . ".h>\n";
  syswrite $fh, "\n";
  syswrite $fh, $impl;

  close $fh;
}
