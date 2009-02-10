/*
 * Copyright (C) 2006 by Marc Boris Duerner, Tommi Maekitalo
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * As a special exception, you may use this file as part of a free
 * software library without restriction. Specifically, if other files
 * instantiate templates or use macros or inline functions from this
 * file, or you compile this file and link it with other files to
 * produce an executable, this file does not by itself cause the
 * resulting executable to be covered by the GNU General Public
 * License. This exception does not however invalidate any other
 * reasons why the executable file might be covered by the GNU Library
 * General Public License.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef CXXTOOLS_NET_TcpServerSocketImpl_H
#define CXXTOOLS_NET_TcpServerSocketImpl_H

#include <string>

namespace cxxtools {

namespace net {

  class TcpServerSocketImpl
  {
    private:
      struct sockaddr_storage servaddr;
      int m_fd;
      int m_timeout;

    public:
      TcpServerSocketImpl()
      {}

      /// creates a server socket and listens on the address
      TcpServerSocketImpl(const std::string& ipaddr, unsigned short int port, int backlog = 5);

      void create(int domain, int type, int protocol);

      void close();

      void listen(const std::string& ipaddr, unsigned short int port, int backlog = 5);

      const struct sockaddr_storage& getAddr() const
      { return servaddr; }

      int fd() const
      { return m_fd; }
  };

} // namespace net

} // namespace cxxtools

#endif // CXXTOOLS_NET_TCPSTREAM_H