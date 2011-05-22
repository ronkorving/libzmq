/*
    Copyright (c) 2007-2011 iMatix Corporation
    Copyright (c) 2007-2011 Other contributors as noted in the AUTHORS file

    This file is part of 0MQ.

    0MQ is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    0MQ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __ZMQ_PAIR_HPP_INCLUDED__
#define __ZMQ_PAIR_HPP_INCLUDED__

#include "socket_base.hpp"
#include "pipe.hpp"

namespace zmq
{

    class pair_t :
        public socket_base_t,
        public i_pipe_events
    {
    public:

        pair_t (class ctx_t *parent_, uint32_t tid_);
        ~pair_t ();

        //  Overloads of functions from socket_base_t.
        void xattach_pipe (class pipe_t *pipe_, const blob_t &peer_identity_);
        int xsend (class msg_t *msg_, int flags_);
        int xrecv (class msg_t *msg_, int flags_);
        bool xhas_in ();
        bool xhas_out ();

        //  i_pipe_events interface implementation.
        void read_activated (class pipe_t *pipe_);
        void write_activated (class pipe_t *pipe_);
        void terminated (class pipe_t *pipe_);

    private:

        //  Hook into termination process.
        void process_term (int linger_);

        class pipe_t *pipe;

        bool terminating;

        pair_t (const pair_t&);
        const pair_t &operator = (const pair_t&);
    };

}

#endif
