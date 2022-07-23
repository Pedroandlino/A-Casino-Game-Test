/*****************************************************************
 * \file	CasinoGame.cpp
 * \brief	Functions and methods for class CasinoGame, to be used with CasinoGame.hpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#include "CasinoGame.hpp"

#include "WindowModel.hpp"
#include "ButtonShape.hpp"
#include "CustomSound.hpp"
#include "PolyParticleShape.hpp"

CasinoGame::CasinoGame(std::shared_ptr<WindowModel> windowModel) :
	m_currentWindow(windowModel),
	m_winSize({ float(windowModel->getSize().x),float(windowModel->getSize().y) }),
	m_numberOfParticleToGenerate(50)
{
}

WindowModel* CasinoGame::getCurrentWindow() {
	return m_currentWindow.get();
}

void CasinoGame::init() {
	loadState();

	initMusic();

	initBackground();
	initStaticTexts();
	initDynamicTexts();
	initParticleObjects();
	initButtons();

	connectParticleObjects();
	connectButtons();

	addShapesToWindow();
}

void CasinoGame::initMusic() {
	std::shared_ptr<CustomSound> mainLoopSound =
		std::shared_ptr<CustomSound>(new CustomSound("MyResources/Sounds/MainLoop.ogg"));
	mainLoopSound->setLoop(true);
	mainLoopSound->play();

	m_soundMap["MainLoop"] = mainLoopSound;
}

void CasinoGame::switchToWindow(std::shared_ptr<WindowModel> windowModel)
{
	m_currentWindow->removeButtons({ m_buttonMap["StartButton"] ,m_buttonMap["CreditsInButton"] ,m_buttonMap["CreditsOutButton"] });
	m_currentWindow = windowModel;
	m_winSize = { float(windowModel->getSize().x),float(windowModel->getSize().y) };
	init();
}

void CasinoGame::loadState()
{
	if (false) {
		//TODO: load from binary file the current State
	}
	else
	{
		m_currentState = State();
	}
}

void CasinoGame::initBackground()
{
	//setup background:
	std::shared_ptr<BoxShape> skyShape =
		std::shared_ptr<BoxShape>(new BoxShape({ m_winSize.x / 2.0f, m_winSize.y / 2.0f }, m_winSize, "MyResources/Textures/background.jpg"));

	std::shared_ptr<BoxShape> topShape =
		std::shared_ptr<BoxShape>(new BoxShape({ m_winSize.x / 2.0f, 0 }, { 1.05f * m_winSize.x , m_winSize.y / 2.3f }, "MyResources/Textures/halfWoodPallet.png"));

	std::shared_ptr<BoxShape> bottomShape =
		std::shared_ptr<BoxShape>(new BoxShape({ m_winSize.x / 2.0f, m_winSize.y }, { 1.05f * m_winSize.x , m_winSize.y / 3.4f }, "MyResources/Textures/halfWoodPallet.png"));
	bottomShape->rotate(180);
	bottomShape->scale({ -1,1 });

	//add to map, in order to be rendered:
	m_shapeMap["Sky"] = { std::dynamic_pointer_cast<WindowInterface>(skyShape) ,int(WindowModel::l0) };
	m_shapeMap["TopShape"] = { std::dynamic_pointer_cast<WindowInterface>(topShape) ,int(WindowModel::l1) };
	m_shapeMap["BottomShape"] = { std::dynamic_pointer_cast<WindowInterface>(bottomShape) ,int(WindowModel::l1) };
}

void CasinoGame::initStaticTexts()
{
	//Static Texts:
	sf::Vector2f shapeSize({ 150,50 });
	float shapeHeight = 37;

	std::shared_ptr<TextShape> playCountText =
		std::shared_ptr<TextShape>(new TextShape("Number of Plays", { (m_winSize.x / 2.0f) - 150 - 20, shapeHeight }, shapeSize));
	playCountText->setTexture("MyResources/Textures/woodPallet.png");

	std::shared_ptr<TextShape> creditsInsertedText =
		std::shared_ptr<TextShape>(new TextShape("Credits Inserted", { (m_winSize.x / 2.0f), shapeHeight }, shapeSize));
	creditsInsertedText->setTexture("MyResources/Textures/woodPallet.png");

	std::shared_ptr<TextShape> creditsRemovedText =
		std::shared_ptr<TextShape>(new TextShape("Credits Removed", { (m_winSize.x / 2.0f) + 150 + 20, shapeHeight }, shapeSize));
	creditsRemovedText->setTexture("MyResources/Textures/woodPallet.png");


	//add to map, in order to be rendered:
	m_shapeMap["PlayCountText"] = { std::dynamic_pointer_cast<WindowInterface>(playCountText) ,int(WindowModel::l2) };
	m_shapeMap["CreditsInsertedText"] = { std::dynamic_pointer_cast<WindowInterface>(creditsInsertedText) ,int(WindowModel::l2) };
	m_shapeMap["CreditsRemovedText"] = { std::dynamic_pointer_cast<WindowInterface>(creditsRemovedText) ,int(WindowModel::l2) };
}

void CasinoGame::initDynamicTexts()
{
	//Dynamic Texts:
	sf::Vector2f shapeSize = { 100,40 };
	float shapeHeight = 35 + 50;

	//TODO: remove 25, replace with scalablility by container, and posterior set
	std::shared_ptr<TextShape> playCountValueText =
		std::shared_ptr<TextShape>(new TextShape(std::to_string(m_currentState.playCount), { (m_winSize.x / 2.0f) - 150 - 20, shapeHeight }, shapeSize, 25));
	playCountValueText->setTexture("MyResources/Textures/woodPallet.png");
	playCountValueText->setUpdateSound("MyResources/Sounds/bling.ogg");

	std::shared_ptr<TextShape> creditsInsertedValueText =
		std::shared_ptr<TextShape>(new TextShape(std::to_string(m_currentState.insertCount), { (m_winSize.x / 2.0f), shapeHeight }, shapeSize, 25));
	creditsInsertedValueText->setTexture("MyResources/Textures/woodPallet.png");
	creditsInsertedValueText->setUpdateSound("MyResources/Sounds/bling.ogg");

	std::shared_ptr<TextShape> creditsRemovedValueText =
		std::shared_ptr<TextShape>(new TextShape(std::to_string(m_currentState.removeCount), { (m_winSize.x / 2.0f) + 150 + 20, shapeHeight }, shapeSize, 25));
	creditsRemovedValueText->setTexture("MyResources/Textures/woodPallet.png");
	creditsRemovedValueText->setUpdateSound("MyResources/Sounds/bling.ogg");

	//add to map, in order to be rendered:
	m_shapeMap["PlayCountValueText"] = { std::dynamic_pointer_cast<WindowInterface>(playCountValueText) ,int(WindowModel::l2) };
	m_shapeMap["CreditsInsertedValueText"] = { std::dynamic_pointer_cast<WindowInterface>(creditsInsertedValueText) ,int(WindowModel::l2) };
	m_shapeMap["CreditsRemovedValueText"] = { std::dynamic_pointer_cast<WindowInterface>(creditsRemovedValueText) ,int(WindowModel::l2) };
}

void CasinoGame::initParticleObjects() {
	std::string nameID;
	std::shared_ptr<PolyParticleShape> particleObject;
	for (int i = 0; i < m_numberOfParticleToGenerate; i++) {
		particleObject =
			std::shared_ptr<PolyParticleShape>(new PolyParticleShape({ (m_winSize.x / 2.0f),(m_winSize.y / 2.0f) }, 10, 20, sf::Color::White));
		particleObject->setTexture("MyResources/Textures/gold.jpg");
		particleObject->setBirthSound("MyResources/Sounds/jumpIn.ogg");
		particleObject->setDeathSound("MyResources/Sounds/jumpOut.ogg");

		particleObject->randomizeColor();
		particleObject->setRandomBirthStateParams(m_winSize);
		particleObject->setupRandomBirthState();

		nameID = "JumpObject" + std::to_string(i);
		m_shapeMap[nameID] = { std::dynamic_pointer_cast<WindowInterface>(particleObject) ,int(WindowModel::l3) };
		m_particleMap[nameID] = std::dynamic_pointer_cast<ParticleInterface>(particleObject);
	}
}

void CasinoGame::connectParticleObjects() {
	//connect particles to other elements of the game

	for (std::pair<std::string, std::shared_ptr<ParticleInterface> > particlePair : m_particleMap) {
		std::map<std::string, void*> argsMap;
		argsMap["textObject"] = (void*)(m_shapeMap["PlayCountValueText"].first.get());
		argsMap["particleMap"] = &m_particleMap;
		argsMap["trackValues"] = &m_currentState;
		argsMap["currentParticle"] = (void*)(m_particleMap[particlePair.first].get());
		argsMap["startButton"] = (void*)(m_shapeMap["StartButton"].first.get());
		particlePair.second->setDeathCondition(&CasinoGame::particleDeathCondition, argsMap);
	}
}


void CasinoGame::initButtons()
{
	//buttons:
	sf::Vector2f shapeSize = { 150,50 };
	float shapeHeight = m_winSize.y - 37;

	std::shared_ptr<ButtonShape> startButton =
		std::shared_ptr<ButtonShape>(new ButtonShape("START", { (m_winSize.x / 2.0f) - 150 - 20, shapeHeight }, shapeSize, sf::Color::Yellow, sf::Color::White));
	startButton->setTexture("MyResources/Textures/cristalButton.png", BoxShape::Mask0);
	startButton->setTexture("MyResources/Textures/chessButton.png", BoxShape::Mask1);
	startButton->swapTexture(BoxShape::Mask0);
	startButton->setHoverSound("MyResources/Sounds/hover.ogg");

	std::shared_ptr<ButtonShape> creditsInButton =
		std::shared_ptr<ButtonShape>(new ButtonShape("CREDITS IN", { (m_winSize.x / 2.0f), shapeHeight }, shapeSize, sf::Color::Green, sf::Color::White));
	creditsInButton->setTexture("MyResources/Textures/cristalButton.png");
	creditsInButton->setHoverSound("MyResources/Sounds/hover.ogg");

	std::shared_ptr<ButtonShape> creditsOutButton =
		std::shared_ptr<ButtonShape>(new ButtonShape("CREDITS OUT", { (m_winSize.x / 2.0f) + 150 + 20, shapeHeight }, shapeSize, sf::Color::Red, sf::Color::White));
	creditsOutButton->setTexture("MyResources/Textures/cristalButton.png");
	creditsOutButton->setHoverSound("MyResources/Sounds/hover.ogg");

	//add to map, in order to be rendered:
	m_shapeMap["StartButton"] = { std::dynamic_pointer_cast<WindowInterface>(startButton) ,int(WindowModel::l2) };
	m_shapeMap["CreditsInButton"] = { std::dynamic_pointer_cast<WindowInterface>(creditsInButton) ,int(WindowModel::l2) };
	m_shapeMap["CreditsOutButton"] = { std::dynamic_pointer_cast<WindowInterface>(creditsOutButton) ,int(WindowModel::l2) };

	//also add them to button internal map:
	m_buttonMap["StartButton"] = std::dynamic_pointer_cast<ButtonInterface>(startButton);
	m_buttonMap["CreditsInButton"] = std::dynamic_pointer_cast<ButtonInterface>(creditsInButton);
	m_buttonMap["CreditsOutButton"] = std::dynamic_pointer_cast<ButtonInterface>(creditsOutButton);
}

void CasinoGame::connectButtons()
{
	//connect buttons to mouse and window
	if (m_shapeMap.count("StartButton") != 0) {
		std::map<std::string, void*> argsMap;
		argsMap["textObject"] = (void*)(m_shapeMap["CreditsInsertedValueText"].first.get());
		argsMap["currentButton"] = (void*)(m_shapeMap["StartButton"].first.get());
		argsMap["particleMap"] = &m_particleMap;
		argsMap["trackValues"] = &m_currentState;
		m_buttonMap["StartButton"]->setClickCallback(&CasinoGame::onStartButton, argsMap);
	}

	if (m_shapeMap.count("CreditsInButton") != 0) {
		std::map<std::string, void*> argsMap;
		argsMap["textObject"] = (void*)(m_shapeMap["CreditsInsertedValueText"].first.get());
		argsMap["trackValues"] = &m_currentState;
		m_buttonMap["CreditsInButton"]->setClickCallback(&CasinoGame::onCreditsInButton, argsMap);
	}

	if (m_shapeMap.count("CreditsOutButton") != 0) {
		std::map<std::string, void*> argsMap;
		argsMap["incrementObject"] = (void*)(m_shapeMap["CreditsRemovedValueText"].first.get());
		argsMap["decrementObject"] = (void*)(m_shapeMap["CreditsInsertedValueText"].first.get());
		argsMap["trackValues"] = &m_currentState;
		m_buttonMap["CreditsOutButton"]->setClickCallback(&CasinoGame::onCreditsOutButton, argsMap);
	}
}

void CasinoGame::updateButtonsOnWindowEvent(const sf::Event& evnt)
{
	for (std::pair<std::string, std::shared_ptr<ButtonInterface>> button : m_buttonMap) {
		if (button.second != nullptr) {
			button.second->onWindowEvent(m_currentWindow.get(), evnt);
		}
	}
}

void CasinoGame::updatePhysics(float deltaTime)
{
	//update physics
	m_currentState.playOngoing = false;//assume all particles are dead

	for (std::pair<std::string, std::shared_ptr<ParticleInterface>> particle : m_particleMap) {
		if (particle.second != nullptr) {

			//update physics
			if (!m_currentState.physicsPaused) {
				particle.second->updatePhysics(deltaTime);
			}

			//check if play is still ongoing
			if (!m_currentState.playOngoing && particle.second->isAlive()) {
				m_currentState.playOngoing = true; //some particles are still alive
			}
		}
	}
}

void CasinoGame::addShapesToWindow()
{
	std::vector<std::pair<std::shared_ptr<WindowInterface>, int>> orderedShapes;

	for (const std::pair<const std::string, std::pair<std::shared_ptr<WindowInterface>, int>>& shape : m_shapeMap) {
		orderedShapes.push_back(shape.second);
	}

	//sort render order (increasing)
	std::sort(orderedShapes.begin(), orderedShapes.end(),
		[](const std::pair <std::shared_ptr<WindowInterface>, int>& a,
			const std::pair <std::shared_ptr<WindowInterface>, int>& b)
		{
			return a.second < b.second;
		});

	for (const std::pair <std::shared_ptr<WindowInterface>, int>& shape : orderedShapes) {
		m_currentWindow->addChild(shape.first);
	}
}

void CasinoGame::onStartButton(std::map<std::string, void*> argsMap)
{
	if (argsMap.count("trackValues") != 0) {//regen arg
		State* statePtr = dynamic_cast<State*>((State*)argsMap["trackValues"]);
		if (statePtr != nullptr) {

			//toggle pause state, if play ongoing
			if (statePtr->playOngoing) {
				//pause/play behaviour
				statePtr->physicsPaused = !statePtr->physicsPaused;

				if (argsMap.count("currentButton") != 0) { //regen arg
					ButtonShape* buttonPtr = dynamic_cast<ButtonShape*>((ButtonShape*)argsMap["currentButton"]);
					if (buttonPtr != nullptr) {
						if (statePtr->physicsPaused) {
							buttonPtr->resetContent("START");
						}
						else {
							buttonPtr->resetContent("PAUSE");
						}
					}
				}
			}

			else if (statePtr->insertCount > 0) {
				//start button behaviour
				statePtr->insertCount--;//decrement value
				statePtr->physicsPaused = false;

				if (argsMap.count("textObject") != 0) { //regen arg
					TextShape* textPtr = dynamic_cast<TextShape*>((TextShape*)argsMap["textObject"]);
					if (textPtr != nullptr) {
						//set value on view
						textPtr->resetContent(std::to_string(statePtr->insertCount));
					}
				}

				if (argsMap.count("particleMap") != 0) { //regen arg
					std::map<std::string, std::shared_ptr<ParticleInterface>>* particleMap =
						dynamic_cast<std::map<std::string, std::shared_ptr<ParticleInterface>>*>(
							(std::map<std::string, std::shared_ptr<ParticleInterface>>*)argsMap["particleMap"]);
					if (particleMap != nullptr) {
						//rebirth Objects
						for (std::pair<std::string, std::shared_ptr<ParticleInterface>> particlePair : *particleMap) {
							particlePair.second->resetToBirthState();
							particlePair.second->birth();
						}
					}
				}

				//issue the start of play, by setting start button to pause:
				if (argsMap.count("currentButton") != 0) { //regen arg
					ButtonShape* buttonPtr = dynamic_cast<ButtonShape*>((ButtonShape*)argsMap["currentButton"]);
					if (buttonPtr != nullptr) {
						buttonPtr->resetContent("PAUSE");
						buttonPtr->swapTexture(BoxShape::Mask1);
					}
				}
			}
		}
	}
}

void CasinoGame::onCreditsInButton(std::map<std::string, void*> argsMap) {
	if (argsMap.count("trackValues") != 0) {//regen arg
		State* statePtr = dynamic_cast<State*>((State*)argsMap["trackValues"]);
		if (statePtr != nullptr) {
			statePtr->insertCount++;//increment value

			if (argsMap.count("textObject") != 0) { //regen arg
				TextShape* textPtr = dynamic_cast<TextShape*>((TextShape*)argsMap["textObject"]);
				if (textPtr != nullptr) {
					//set value on view
					textPtr->resetContent(std::to_string(statePtr->insertCount));
				}
			}
		}
	}
}

void CasinoGame::onCreditsOutButton(std::map<std::string, void*> argsMap) {
	if (argsMap.count("trackValues") != 0) {//regen arg
		State* statePtr = dynamic_cast<State*>((State*)argsMap["trackValues"]);
		if (statePtr != nullptr) {
			if (statePtr->insertCount > 0) {

				statePtr->removeCount++;//increment value

				if (argsMap.count("incrementObject") != 0) { //regen arg
					TextShape* textPtr = dynamic_cast<TextShape*>((TextShape*)argsMap["incrementObject"]);
					if (textPtr != nullptr) {
						//set value on view
						textPtr->resetContent(std::to_string(statePtr->removeCount));
					}
				}

				statePtr->insertCount--;//decrement value

				if (argsMap.count("decrementObject") != 0) { //regen arg
					TextShape* textPtr = dynamic_cast<TextShape*>((TextShape*)argsMap["decrementObject"]);
					if (textPtr != nullptr) {
						//set value on view
						textPtr->resetContent(std::to_string(statePtr->insertCount));
					}
				}
			}
		}
	}
}

bool CasinoGame::particleDeathCondition(std::map<std::string, void*> argsMap)
{
	bool killCurrentParticle = false;//by default, stay alive

	if (argsMap.count("currentParticle") != 0) {//regen arg
		ParticleInterface* particlePtr = dynamic_cast<ParticleInterface*>((ParticleInterface*)argsMap["currentParticle"]);
		if (particlePtr != nullptr)
		{
			//check current particle state:
			if (particlePtr->isAlive() && particlePtr->getState().position.x < 0.0f)
			{
				killCurrentParticle = true;//kill it
			}

			//on known deadth, check if play count should increment:
			if (killCurrentParticle && argsMap.count("particleMap") != 0) { //regen arg
				std::map<std::string, std::shared_ptr<ParticleInterface>>* particleMap =
					dynamic_cast<std::map<std::string, std::shared_ptr<ParticleInterface>>*>(
						(std::map<std::string, std::shared_ptr<ParticleInterface>>*)argsMap["particleMap"]);
				if (particleMap != nullptr) {
					//check if particle objects are dead:
					bool allParticlesAreDead = true;
					for (std::pair<std::string, std::shared_ptr<ParticleInterface>> particlePair : *particleMap) {
						if (particlePair.second.get() != particlePtr && particlePair.second->isAlive()) {
							allParticlesAreDead = false;
						}
					}

					//update play count:
					if (allParticlesAreDead) {
						if (argsMap.count("trackValues") != 0) {//regen arg
							State* statePtr = dynamic_cast<State*>((State*)argsMap["trackValues"]);
							if (statePtr != nullptr) {
								statePtr->playCount++;//increment value
								if (argsMap.count("textObject") != 0) { //regen arg
									TextShape* textPtr = dynamic_cast<TextShape*>((TextShape*)argsMap["textObject"]);
									if (textPtr != nullptr) {
										//set value on view
										textPtr->resetContent(std::to_string(statePtr->playCount));
									}
								}
							}
						}

						//issue the end of play, by setting start button to play:
						if (argsMap.count("startButton") != 0) { //regen arg
							ButtonShape* buttonPtr = dynamic_cast<ButtonShape*>((ButtonShape*)argsMap["startButton"]);
							if (buttonPtr != nullptr) {
								buttonPtr->resetContent("PLAY");
								buttonPtr->swapTexture(BoxShape::Mask0);
							}
						}

					}//else, do nothing
				}
			}
		}
	}

	return killCurrentParticle;
}