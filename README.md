# 🖼️ BMP Handler (2022)

<p align="center">
  <img src="https://github.com/kenzohj/BMP-Handler/blob/main/home.png" alt="Home page" width="800" />
</p>

**🇫🇷 Français | [🇬🇧 English below](#-english-version-)**  

---

## 📌 À propos du projet  

**BMP Handler** est un projet réalisé en **1ʳᵉ année de BUT Informatique** permettant d'appliquer divers traitements sur une image **BMP**.  

Ce projet a été développé par :  
- [Kenzo Hambli](https://github.com/KenzoHJ)  
- [Baptiste Monsterleet](https://github.com/MonsterleetB)  
- [Nicolas Toupin](https://github.com/Zeidxn)  

📜 **Fonctionnalités** :  
✔️ Passage en **niveaux de gris**  
✔️ **Inversion des couleurs**  
✔️ **Conversion monochrome**  
✔️ **Extraction des contours**  
✔️ **Superposition de 2 images BMP**  

Le traitement d'image a été **entièrement réalisé en C**, **sans bibliothèque externe**.  

### ⚠️ Remarque importante  
Les fichiers **index.py** et **lancer_interface.py** nous ont été **fournis** et n'ont pas été développés par nous.  

---

## 🎨 Interface Web  

L'interface web a été développée par **Kenzo Hambli** et permet d'appliquer les traitements de manière intuitive.  

### 🛠️ Utilisation via l'interface web  

1️⃣ **Lancer le serveur local**  
Exécutez **`lancer_interface.py`**, cela créera un **serveur local** et ouvrira automatiquement la page web.  

2️⃣ **Placer les images BMP**  
Les images à traiter doivent être placées **dans le même dossier** que `lancer_interface.py`.  

3️⃣ **Choisir un traitement**  
Sélectionnez une image puis appliquez un traitement.  

4️⃣ **Récupérer l'image traitée**  
L'image résultante sera enregistrée sous le nom **`result.bmp`** dans le même dossier.  

---

## 🖥️ Utilisation via l'exécutable  

1️⃣ **Lancer le programme**  
Exécutez le fichier **`SAeimages.exe`** dans un terminal ou en double-cliquant dessus.  

2️⃣ **Suivre les instructions**  
Un menu interactif apparaîtra vous demandant de :  
   - Choisir un type de transformation
   - Sélectionner une image à traiter
   - (Si nécessaire) Ajouter une seconde image pour la superposition

3️⃣ **Récupérer l'image traitée**  
L'image transformée sera enregistrée sous le nom **`result.bmp`** dans le même dossier que l'exécutable.  

---

## 📝 Licence  

Ce projet a été développé dans un cadre scolaire et n'est pas destiné à un usage commercial.  

---

## 🇬🇧 English Version  

## 📌 About the project  

**BMP Handler** is a project developed during our **1st year of a Computer Science Bachelor’s program (BUT Informatique)**. It allows applying various transformations on a **BMP image**.  

Developed by:  
- [Kenzo Hambli](https://github.com/KenzoHJ)  
- [Baptiste Monsterleet](https://github.com/MonsterleetB)  
- [Nicolas Toupin](https://github.com/Zeidxn)  

📜 **Features**:  
✔️ **Grayscale conversion**  
✔️ **Color inversion**  
✔️ **Monochrome transformation**  
✔️ **Edge detection**  
✔️ **Overlay of 2 BMP images**  

The image processing was **entirely written in C**, **without any external library**.  

### ⚠️ Important Note  
The files **index.py** and **lancer_interface.py** were **provided to us** and were not developed by our team.  

---

## 🎨 Web Interface  

The web interface was developed by **Kenzo Hambli** to allow intuitive usage.  

### 🛠️ How to use via web interface  

1️⃣ **Start the local server**  
Run **`lancer_interface.py`**, which will create a **local server** and automatically open the web page.  

2️⃣ **Place BMP images**  
The images must be placed **in the same directory** as `lancer_interface.py`.  

3️⃣ **Select a transformation**  
Choose an image then apply a transformation.  

4️⃣ **Retrieve the processed image**  
The resulting image will be saved as **`result.bmp`** in the same folder.  

---

## 🖥️ How to use via the executable  

1️⃣ **Launch the program**  
Run the **`SAeimages.exe`** file from a terminal or by double-clicking it.  

2️⃣ **Follow the instructions**  
An interactive menu will appear asking you to:  
   - Choose a transformation type  
   - Select an image to process  
   - (If required) Provide a second image for overlay  

3️⃣ **Retrieve the processed image**  
The processed image will be saved as **`result.bmp`** in the same folder as the executable.  

---

## 📝 License  

This project was developed for educational purposes and is not intended for commercial use.  
