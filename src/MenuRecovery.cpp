#include "MenuRecovery.hpp"
#include "HeistModifier.hpp"
#include "StatEditor.hpp"
#include "Transactions.hpp"
#include "Unlocker.hpp"
#include "DailyActivities.hpp"
#include "Items.hpp"
#include <memory>

namespace YimMenu::Submenus
{
	Recovery::Recovery() :
#define ICON_FA_SACK_DOLLAR "\xef\x93\x80"
	    Submenu::Submenu("Recovery", ICON_FA_SACK_DOLLAR)
	{
		auto main = std::make_shared<Category>("Main");
		auto businesses = std::make_shared<Category>("Businesses");
		auto casino = std::make_shared<Category>("Casino");

		auto generalGroup = std::make_shared<Group>("General");
		auto businessSafe = std::make_shared<Group>("Business Safe");
		auto businessOverlay = std::make_shared<Group>("Business Overlay", 2);
		auto businessManager = std::make_shared<Group>("Business Manager", 4);
		auto casinoSlots = std::make_shared<Group>("Slot Machines");
		//auto casinoWheel = std::make_shared<Group>("Lucky Wheel");
		//auto casinoBlackJack = std::make_shared<Group>("Blackjack");
		//auto casinoRoulette = std::make_shared<Group>("Roulette");

		generalGroup->AddItem(std::make_shared<BoolCommandItem>("playallmissionssolo"_J));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("unlockgtaplus"_J));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("overriderpmultiplier"_J));
		generalGroup->AddItem(std::make_shared<ConditionalItem>("overriderpmultiplier"_J, std::make_shared<FloatCommandItem>("rpmultiplierinput"_J)));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("freechangeappearance"_J));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("nochangeappearancecooldown"_J));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("allowgenderchange"_J));
		businessSafe->AddItem(std::make_shared<ListCommandItem>("businesssafe"_J));
		businessSafe->AddItem(std::make_shared<CommandItem>("claimsafeearnings"_J));

		businessOverlay->AddItem(std::make_shared<BoolCommandItem>("businessoverlay"_J));
		businessOverlay->AddItem(std::make_shared<ConditionalItem>("businessoverlay"_J, std::make_shared<BoolCommandItem>("showwarehouse"_J)));
		businessOverlay->AddItem(std::make_shared<ConditionalItem>("businessoverlay"_J, std::make_shared<BoolCommandItem>("showhangar"_J)));
		businessOverlay->AddItem(std::make_shared<ConditionalItem>("businessoverlay"_J, std::make_shared<BoolCommandItem>("showbusinesses"_J)));
		businessOverlay->AddItem(std::make_shared<ConditionalItem>("businessoverlay"_J, std::make_shared<BoolCommandItem>("shownightclub"_J)));

		businessManager->AddItem(std::make_shared<CommandItem>("resupplybusiness"_J));
		businessManager->AddItem(std::make_shared<CommandItem>("hangerresupply"_J));
		businessManager->AddItem(std::make_shared<CommandItem>("warehouseresupply"_J));
		businessManager->AddItem(std::make_shared<CommandItem>("nightclubpopularity"_J));
		businessManager->AddItem(std::make_shared<CommandItem>("salvageyardpopularity"_J));
		businessManager->AddItem(std::make_shared<CommandItem>("moneyfrontheatremove"_J));
		businessManager->AddItem(std::make_shared<BoolCommandItem>("removeresupplycooldown"_J));
		businessManager->AddItem(std::make_shared<BoolCommandItem>("enforceeasiestmission"_J));


		casinoSlots->AddItem(std::make_shared<BoolCommandItem>("casinomanipulaterigslotmachines"_J));


		main->AddItem(generalGroup);
		businesses->AddItem(businessSafe);
		businesses->AddItem(businessOverlay);
		businesses->AddItem(businessManager);
		casino->AddItem(casinoSlots);

		AddCategory(std::move(main));
		AddCategory(std::move(businesses));
		AddCategory(BuildHeistModifierMenu());
		AddCategory(BuildDailyActivitiesMenu());
		AddCategory(BuildStatEditorMenu());
		AddCategory(BuildTransactionsMenu());
		AddCategory(std::move(casino));
		AddCategory(BuildUnlockerMenu());
	}
}