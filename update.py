import wget
import os
import requests
import json

URL = "https://api.github.com/repos/Konohamaru04/Wallpaper-Engine/releases/latest"
user_data = requests.get(URL).json()
jsonObj = json.dumps(user_data, indent = 4)
a = json.loads(jsonObj)
b = a["assets"] 
url = ""
name = a["name"]
new = a["body"]
version = a["tag_name"]
for x in b:
    abc = json.dumps(x, indent = 4)
    pqr = json.loads(abc)
    url = pqr["browser_download_url"]
if os.path.exists("updates"):
    print(f"What's new in {version}: \n{new}\n")
    print(f"Downloading {name}")
else:
    os.mkdir("updates")
    print(f"What's new in {version}: \n{new}\n")
    print(f"Downloading {name}")
if wget.download(url, 'updates/WE_latest.exe'):
    print("\nDownload Complete")
else:
    print("\nDownload failed")
