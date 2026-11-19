# Add this starter kit to your GitHub repository

## 1. Download and extract

Download the ZIP from this chat and extract it. It contains the repository root files and folders.

## 2. Clone your empty GitHub repository

Open Command Prompt or PowerShell and run:

```powershell
cd $HOME\Documents
git clone https://github.com/altafattar14/Solar-Wireless-EV-Car.git
```

## 3. Copy the extracted contents

Copy **all files and folders inside** `Solar-Wireless-EV-Car-Starter` into the newly cloned `Solar-Wireless-EV-Car` folder. Allow the new README.md to replace the initial two-line README.md.

## 4. Commit and push

```powershell
cd $HOME\Documents\Solar-Wireless-EV-Car
git add .
git status
git commit -m "Add project starter files and ESP32 controller"
git push origin main
```

If Git asks you to identify yourself, configure a name and email:

```powershell
git config --global user.name "Your Name"
git config --global user.email "your-github-email@example.com"
```

Use your own GitHub email in place of the example. GitHub may prompt you to authenticate in a browser. Do not paste a password, personal access token, or other secret into chat.

## Alternative: GitHub website

You can also open the repository, choose **Add file → Upload files**, and upload the extracted files. Preserve their folder paths and commit the upload to `main`. The local Git method above is usually more reliable for a folder tree.
