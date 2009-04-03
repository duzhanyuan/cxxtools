/*
 * Copyright (C) 2009 by Dr. Marc Boris Duerner
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
#ifndef cxxtools_xmlrpc_Client_h
#define cxxtools_xmlrpc_Client_h

#include <cxxtools/xmlrpc/api.h>
#include <cxxtools/xmlrpc/fault.h>
#include <cxxtools/xmlrpc/formatter.h>
#include <cxxtools/xmlrpc/scanner.h>
#include <cxxtools/xml/xmlreader.h>
#include <cxxtools/xml/xmlwriter.h>
#include <cxxtools/httpclient.h>
#include <cxxtools/deserializer.h>
#include <cxxtools/serializer.h>
#include <cxxtools/connectable.h>
#include <cxxtools/textstream.h>
#include <string>
#include <cstddef>

namespace cxxtools {

class SelectorBase;

namespace xmlrpc {

class IRemoteProcedure;


class CXXTOOLS_XMLRPC_API Client : public cxxtools::Connectable
{
    enum State
    {
        OnBegin,
        OnMethodResponseBegin,
        OnFaultBegin,
        OnFaultEnd,
        OnFaultResponseEnd,
        OnParamsBegin,
        OnParam,
        OnParamEnd,
        OnParamsEnd,
        OnMethodResponseEnd
    };

    public:
        Client(SelectorBase& selector, const std::string& addr,
               unsigned short port, const std::string& url);

        Client(const std::string& addr, unsigned short port, const std::string& url);

        virtual ~Client();

        void beginCall(IDeserializer& r, IRemoteProcedure& method, ISerializer** argv, unsigned argc);

        void call(IDeserializer& r, IRemoteProcedure& method, ISerializer** argv, unsigned argc);

    protected:
        void onReplyHeader(net::HttpClient& client);

        std::size_t onReplyBody(net::HttpClient& client);

        void onReplyFinished(net::HttpClient& client);

        void prepareRequest(const std::string& name, ISerializer** argv, unsigned argc);

        void advance(const xml::Node& node);

    private:
        State _state;
        std::string _url;
        net::HttpClient _client;
        net::HttpRequest _request;
        TextIStream _ts;
        xml::XmlReader _reader;
        xml::XmlWriter _writer;
        Formatter _formatter;
        Scanner _scanner;
        IRemoteProcedure* _method;
        DeserializationContext _context;
        Deserializer<Fault> _fh;
        Fault _fault;
};

}

}

#endif