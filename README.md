## 2048

C'est un petit projet en C++ qui utilise Qt6 et QML, fait dans le cadre de mes études.  
Pas grand chose à dire dessus, c'est un 2048, tout ce qu'il y a de plus classique.

### Comment on lance ?

#### Clonage du projet
```bash
git clone https://github.com/Pokegali/2048
cd 2048
```

#### Installation des dépendences
```bash
sudo apt install cmake qt6-base-dev qml6-module-qtquick qt6-declarative-dev qml6-module-qtqml qml6-module-qtquick-controls qml6-module-qtquick-dialogs qml6-module-qtquick-window qml6-module-qtquick-layouts qml6-module-qtcore qml6-module-qtqml-workerscript qml6-module-qtquick-templates qml6-module-qt-labs-qmlmodels
```
(À voir si y'en a en trop, mais avec ça, ça marche.)

#### Compilation
```bash
mkdir build
cd build
cmake ..
make
```

Puis après il suffit de lancer l'exécutable.
```bash
./game
```