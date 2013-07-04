/*
 * (C) 2003-2013 Anope Team
 * Contact us at team@anope.org
 *
 * Please read COPYING and README for further details.
 */

#include "module.h"

class StatusUpdate : public Module
{
 public:
	StatusUpdate(const Anope::string &modname, const Anope::string &creator) : Module(modname, creator, VENDOR)
	{

	}

	void OnAccessAdd(ChannelInfo *ci, CommandSource &, ChanAccess *access) anope_override
	{
		if (ci->c)
			for (Channel::ChanUserList::iterator it = ci->c->users.begin(), it_end = ci->c->users.end(); it != it_end; ++it)
			{
				User *user = it->second->user;

				ChanAccess::Path p;
				if (user->server != Me && access->Matches(user, user->Account(), p))
				{
					AccessGroup ag = ci->AccessFor(user);

					for (unsigned i = 0; i < ModeManager::GetStatusChannelModesByRank().size(); ++i)
					{
						ChannelModeStatus *cms = ModeManager::GetStatusChannelModesByRank()[i];
						if (!ag.HasPriv("AUTO" + cms->name))
							ci->c->RemoveMode(NULL, cms, user->GetUID());
					}
					ci->c->SetCorrectModes(user, true);
				}
			}
	}

	void OnAccessDel(ChannelInfo *ci, CommandSource &, ChanAccess *access) anope_override
	{
		if (ci->c)
			for (Channel::ChanUserList::iterator it = ci->c->users.begin(), it_end = ci->c->users.end(); it != it_end; ++it)
			{
				User *user = it->second->user;

				ChanAccess::Path p;
				if (user->server != Me && access->Matches(user, user->Account(), p))
				{
					AccessGroup ag = ci->AccessFor(user);

					for (unsigned i = 0; i < ModeManager::GetStatusChannelModesByRank().size(); ++i)
					{
						ChannelModeStatus *cms = ModeManager::GetStatusChannelModesByRank()[i];
						if (!ag.HasPriv("AUTO" + cms->name))
							ci->c->RemoveMode(NULL, cms, user->GetUID());
					}
				}
			}
	}
};

MODULE_INIT(StatusUpdate)
