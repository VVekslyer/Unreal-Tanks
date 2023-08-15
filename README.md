# Unreal Engine 5 - Tanks

A little game developed using Unreal Engine 5. In this game you control a tank and the goal is to destroy all turrets.

## Mechanics
* Base Pawn class - In this base class implements fire, destruction and turret rotation mechanics. This is a parent class of Tank and Turret class.
* Tank Class - a Pawn that a player controls. Pawn movement was implimanted in this class.
* Turret Class - A Pawn controlled by AI. The turret fires at the player's tank if it in the attack range.
* Projectile Class - An Actor that Tank and Turret spawns when fires. This Actor deals damage.
* Health Component - a Component that takes damage from projectiles. Used by Tank and Turrets.
* Game Mode Class - A Game Mode that keeps track of whether player is alive and whether there there are turrets left. If player dies, the game ends with a lose screen. If all turrets are destroyed, then the game ends with a win screen.

## Getting Started

To get started with this project, you'll need to clone the repository to your local machine. You can do this using GitHub Desktop or by running the following command in a terminal: 
```bash
git clone https://github.com/VVekslyer/TankGame.git
```
Once you have cloned the repository, you can open the project in Unreal Engine by double-clicking on the `.uproject` file.

## Editing the Project

To edit the project, simply make changes to the assets and code within Unreal Engine. When you're ready to save your changes, go to `File` -> `Save All`.

## Pushing Changes

To push your changes to the GitHub repository, you'll need to commit and push them using either GitHub Desktop or a terminal. 
It's easiest to do it through GitHub Desktop.

On GitHub Desktop:

1. Open GitHub Desktop and select this repository from the list on the left.
2. If you've made changes, you will see them in the list of changes. Make sure to do `Save all` before this step.
3. Press the `Commit` button in the bottom left corner.
4. Then press the `Push origin` button in the top right corner.
5. If you go to `Repository` -> `View on GitHub` you will see your changes on the GitHub website.

Behind the scene these program enter git commands for you in the terminal. Here's how to do it using a terminal:

1. Open a terminal and navigate to the root of your local repository.
2. Run `git add .` to stage all changes.
3. Run `git commit -m "Your commit message"` to commit your changes.
4. Run `git push` to push your changes to the remote repository.

It should also be possible to do this through Unreal Engine, as well as Visual Studio. Any method works so long it shows up on the GitHub repo.