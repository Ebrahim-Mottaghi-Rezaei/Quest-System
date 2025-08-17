# QuestSystem Plugin for Unreal Engine 5

A flexible and extensible **Quest System** for Unreal Engine 5, designed for both **gameplay** and **UI integration**.  
Supports multiple quest types, custom conditions, inventory-based objectives, timed quests, and easy integration with Blueprint or C++.

---

## ✨ Features

- **Quest Types**
  - Standard quests
  - Inventory-based quests
  - Timed quests
- **Quest Conditions**
  - `HasCompletedTasks`
  - `HasItemsCondition`
  - Custom condition base class for easy extension
- **Inventory Integration**
  - Built-in `InventoryComponent` for item tracking
- **Data-Driven**
  - `GameplayItemData` Data Assets and `Quest` Object for easy editing in the editor
- **Gameplay Actors**
  - `QuestActor`, `QuestTriggerBox` for world interactions
- **UI Ready**
  - Widget blueprints for displaying quest data and icons
- **Modular Design**
  - C++ and Blueprint friendly
  - Interfaces for quest interaction

---

## 📂 Plugin Structure

```
Source/QuestSystem/
    Components/
        InventoryComponent
        QuestComponent
    DataAssets/
        GameplayItemData
    DataTypes/
        Enums
        Structs
        Delegates
    Gameplay/
        GameplayActors/
            GameplayItem
            QuestActor
            QuestTriggerBox
        QuestSystem/
            Conditions/
                HasCompletedTasks
                HasItemsCondition
                QuestCondition
            InventoryBasedQuest
            Quest
            TimedQuest
    Interfaces/
        QuestInterface
Content/
    Quests/
        Example quest assets
    Widgets/
        Quest UI widgets & icons
Materials/
    Example materials
```

---

## 🚀 Installation

1. Download or clone this repository into your Unreal Engine 5 `Plugins` folder:
   ```
   <YourUEProject>/Plugins/QuestSystem/
   ```
2. Open your project in Unreal Engine 5.
3. Enable the **QuestSystem** plugin in `Edit > Plugins`.
4. Restart the editor.

---

## 📖 Usage

### 1. Adding a Quest
- Create a **Quest Asset** from the editor (`Quest` or `TimedQuest`).
- Define objectives and conditions.
- Assign to a `QuestActor` or trigger.

### 2. Using Inventory Integration
- Add `InventoryComponent` to your player controller or any other actor.
  - That Actor `Must` Implement `QuestInterface` and implement the functions it has. 
- Items defined in `GameplayItemData` can be picked up and tracked.

### 3. Quest Conditions
- Use built-in conditions like `HasItemsCondition` or create custom ones by inheriting from `QuestCondition`.

### 4. UI
- Use provided widgets in `Content/Widgets/QuestSystem` to display quest info.

---

## 🛠 Example
```cpp
UQuestComponent* QuestComp = FindComponentByClass<UQuestComponent>();
if (QuestComp)
    QuestComp->AddQuest(MyQuestData);
```

---

## 📜 License
MIT License
