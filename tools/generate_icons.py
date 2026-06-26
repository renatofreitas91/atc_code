import os
import urllib.request
from pathlib import Path

from PIL import Image


ROOT = Path(__file__).resolve().parents[1]
ICONS_DIR = ROOT / "icons"
PROJECT_DIR = ROOT / "Advanced Trigonometry Calculator"
BASE_ICON = ICONS_DIR / "base_icon.png"
ICON_URL = "https://images.prodia.xyz/8f3b9c7a-9f5b-4c4d-b0a1-468bfb8f72ef.png"


def main() -> None:
    ICONS_DIR.mkdir(exist_ok=True)

    if not BASE_ICON.exists():
        print("A descarregar a imagem base do icone...")
        try:
            urllib.request.urlretrieve(ICON_URL, BASE_ICON)
        except Exception as exc:
            print("Nota: se o download falhar, guarde a imagem como 'icons/base_icon.png' e execute novamente.")
            print(f"Erro do download: {exc}")

    if not BASE_ICON.exists():
        print("Erro: nao foi possivel encontrar a imagem base.")
        return

    img = Image.open(BASE_ICON).convert("RGBA")

    sizes = {
        "icon-16.png": (16, 16),
        "icon-32.png": (32, 32),
        "icon-48.png": (48, 48),
        "icon-192.png": (192, 192),
        "icon-512.png": (512, 512),
    }

    print("A gerar os diferentes formatos PNG...")
    for name, size in sizes.items():
        resized = img.resize(size, Image.Resampling.LANCZOS)
        output = ICONS_DIR / name
        resized.save(output)
        print(f" -> Criado: {output.relative_to(ROOT)} ({size[0]}x{size[1]})")

    ico_path = PROJECT_DIR / "icon.ico"
    img.save(
        ico_path,
        format="ICO",
        sizes=[(16, 16), (32, 32), (48, 48), (256, 256)],
    )
    print(f" -> Criado: {ico_path.relative_to(ROOT)}")

    print("\nTodos os formatos foram gerados com sucesso.")


if __name__ == "__main__":
    main()
