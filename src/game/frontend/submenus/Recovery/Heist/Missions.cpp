#include "Missions.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<TabItem> RenderMissionsMenu()
	{
        auto tab = std::make_shared<TabItem>("Missions");


        auto setups = std::make_shared<Group>("Mission Setups",2);
        auto lowrider = std::make_shared<Group>("Low Rider",2);
        auto casino = std::make_shared<Group>("Casino",2);
        auto yach = std::make_shared<Group>("Yach",2);
        auto papertrail = std::make_shared<Group>("Papertrail",2);
        auto dragwar = std::make_shared<Group>("Dragwars",2);
        auto mercenaries = std::make_shared<Group>("Mercenaries",2);
        auto cluckinbell = std::make_shared<Group>("Cluckin Bell",2);
        auto tuners = std::make_shared<Group>("Tuners",4);
        auto contract = std::make_shared<Group>("Contract",4);
        auto chopshop = std::make_shared<Group>("Chopshop",2);


        lowrider->AddItem(std::make_shared<ListCommandItem>("lowridermission"_J));
        lowrider->AddItem(std::make_shared<CommandItem>("lowridersetup"_J));

        casino->AddItem(std::make_shared<ListCommandItem>("casinostorymission"_J));
        casino->AddItem(std::make_shared<CommandItem>("casinostorysetup"_J));

        yach->AddItem(std::make_shared<ListCommandItem>("superyachtmission"_J));
        yach->AddItem(std::make_shared<CommandItem>("superyachtmissionsetup"_J));

        papertrail->AddItem(std::make_shared<ListCommandItem>("operationpapertrailmission"_J));
        papertrail->AddItem(std::make_shared<CommandItem>("operationpapertrailsetup"_J));

        dragwar->AddItem(std::make_shared<ListCommandItem>("drugwarsmission"_J));
        dragwar->AddItem(std::make_shared<CommandItem>("drugwarsmissionsetup"_J));

        mercenaries->AddItem(std::make_shared<ListCommandItem>("samerccmission"_J));
        mercenaries->AddItem(std::make_shared<CommandItem>("samerccmissionsetup"_J));

        cluckinbell->AddItem(std::make_shared<ListCommandItem>("cluckinbellfarmraidmission"_J));
        cluckinbell->AddItem(std::make_shared<CommandItem>("cluckinbellfarmraidsetup"_J));

        tuners->AddItem(std::make_shared<ListCommandItem>("tunersrobbery"_J));
        tuners->AddItem(std::make_shared<CommandItem>("tunerscompletepreps"_J));
        tuners->AddItem(std::make_shared<CommandItem>("tunersresetpreps"_J));
        tuners->AddItem(std::make_shared<CommandItem>("tunersresetcontracts"_J));
        tuners->AddItem(std::make_shared<CommandItem>("tunersrobberysetup"_J));

        contract->AddItem(std::make_shared<ListCommandItem>("contractmissions"_J));
        contract->AddItem(std::make_shared<CommandItem>("contractmissionssetup"_J));

        chopshop->AddItem(std::make_shared<ListCommandItem>("chopshoprobbery"_J));
        chopshop->AddItem(std::make_shared<CommandItem>("chopshoprobberysetup"_J));
        

        tab->AddItem(lowrider);
        tab->AddItem(casino);
        tab->AddItem(yach);
        tab->AddItem(papertrail);
        tab->AddItem(dragwar);
        tab->AddItem(mercenaries);
        tab->AddItem(cluckinbell);
        tab->AddItem(tuners);
        tab->AddItem(contract);
        tab->AddItem(chopshop);

        return tab;
    
    }
}