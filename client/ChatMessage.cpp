/*
 * Copyright (C) 2001-2013 Jacek Sieka, arnetheduck on gmail point com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "stdinc.h"
#include "OnlineUser.h"
#include "ChatMessage.h"

string ChatMessage::format(/*const bool fullFormat [!] TODO */) const
{
	dcassert(m_from); // [!] IRainman fix: You can not generate this event anonymously! Initialize 'from' user - initiated sending a message!
	string tmp;
	
	if (m_timestamp)
	{
		tmp += '[' + Util::getShortTimeString(m_timestamp) + "] ";
	}
	/* [!] IRainman TODO: please don't delete this! Needs for WebAPI!
	if (fullFormat)
	{
	    tmp += formatNick(from->getIdentity().getNick(), thirdPerson) + text;
	}
	else
	   [!] IRainman TODO */
	{
		tmp += m_text;
	}
	
	// Check all '<' and '[' after newlines as they're probably pastes...
	size_t i = 0;
	while ((i = tmp.find('\n', i)) != string::npos)
	{
		if (i + 1 < tmp.length())
		{
			if (tmp[i + 1] == '[' || tmp[i + 1] == '<')
			{
				tmp.insert(i + 1, "- ");
				i += 2;
			}
		}
		i++;
	}
	
	return Text::toDOS(tmp);
}
