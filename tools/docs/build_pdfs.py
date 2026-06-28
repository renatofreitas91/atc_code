from __future__ import annotations

import argparse
import re
from pathlib import Path

from reportlab.lib import colors
from reportlab.lib.enums import TA_LEFT
from reportlab.lib.pagesizes import A4
from reportlab.lib.styles import ParagraphStyle, getSampleStyleSheet
from reportlab.lib.units import mm
from reportlab.platypus import (
    PageBreak,
    Paragraph,
    Preformatted,
    SimpleDocTemplate,
    Spacer,
)


ROOT = Path(__file__).resolve().parents[2]

DOCUMENTS = [
    ("docs/en/User_Guide.md", "docs/pdf/ATC_User_Guide_EN.pdf", "ATC User Guide"),
    ("docs/pt-PT/User_Guide.md", "docs/pdf/ATC_User_Guide_PT-PT.pdf", "Guia de Utilizador do ATC"),
    ("docs/en/User_Guide_Full.md", "docs/pdf/ATC_Full_User_Guide_EN.pdf", "ATC Full User Guide"),
    ("docs/pt-PT/User_Guide_Full.md", "docs/pdf/ATC_Full_User_Guide_PT-PT.pdf", "Guia Completo de Utilizador do ATC"),
    ("docs/en/ATC_Cookbook.md", "docs/pdf/ATC_Cookbook_EN.pdf", "ATC Cookbook"),
    ("docs/pt-PT/ATC_Cookbook.md", "docs/pdf/ATC_Cookbook_PT-PT.pdf", "Cookbook do ATC"),
    ("docs/en/Best_Practices.md", "docs/pdf/ATC_Best_Practices_EN.pdf", "ATC Best Practices"),
    ("docs/pt-PT/Best_Practices.md", "docs/pdf/ATC_Best_Practices_PT-PT.pdf", "Boas Praticas do ATC"),
    ("docs/en/Developer_Guide.md", "docs/pdf/ATC_Developer_Guide_EN.pdf", "ATC Developer Guide"),
    ("docs/pt-PT/Developer_Guide.md", "docs/pdf/ATC_Developer_Guide_PT-PT.pdf", "Guia de Developer do ATC"),
    ("docs/en/Developer_Reference.md", "docs/pdf/ATC_Developer_Reference_EN.pdf", "ATC Developer Reference"),
    ("docs/pt-PT/Developer_Reference.md", "docs/pdf/ATC_Developer_Reference_PT-PT.pdf", "Referencia de Developer do ATC"),
    ("docs/en/Architecture.md", "docs/pdf/ATC_Architecture_EN.pdf", "ATC Architecture"),
    ("docs/pt-PT/Architecture.md", "docs/pdf/ATC_Architecture_PT-PT.pdf", "Arquitetura do ATC"),
    ("docs/en/Testing.md", "docs/pdf/ATC_Testing_EN.pdf", "ATC Testing"),
    ("docs/pt-PT/Testing.md", "docs/pdf/ATC_Testing_PT-PT.pdf", "Testes do ATC"),
    ("docs/en/RELEASE_2.1.7.md", "docs/pdf/ATC_Release_2.1.7_EN.pdf", "ATC 2.1.7 Release Notes"),
    ("docs/pt-PT/RELEASE_2.1.7.md", "docs/pdf/ATC_Release_2.1.7_PT-PT.pdf", "Notas de Release ATC 2.1.7"),
]


def escape_text(text: str) -> str:
    return (
        text.replace("&", "&amp;")
        .replace("<", "&lt;")
        .replace(">", "&gt;")
    )


def normalize_inline_markdown(text: str) -> str:
    text = escape_text(text)
    text = re.sub(r"`([^`]+)`", r"<font name='Courier'>\1</font>", text)
    text = re.sub(r"\*\*([^*]+)\*\*", r"<b>\1</b>", text)
    text = re.sub(r"\[([^\]]+)\]\(([^)]+)\)", r"\1", text)
    return text


def build_styles():
    base = getSampleStyleSheet()
    return {
        "title": ParagraphStyle(
            "ATCTitle",
            parent=base["Title"],
            fontName="Helvetica-Bold",
            fontSize=20,
            leading=24,
            spaceAfter=10,
            textColor=colors.HexColor("#1F4E79"),
        ),
        "h1": ParagraphStyle(
            "ATCH1",
            parent=base["Heading1"],
            fontName="Helvetica-Bold",
            fontSize=16,
            leading=20,
            spaceBefore=12,
            spaceAfter=6,
            textColor=colors.HexColor("#1F4E79"),
        ),
        "h2": ParagraphStyle(
            "ATCH2",
            parent=base["Heading2"],
            fontName="Helvetica-Bold",
            fontSize=13,
            leading=16,
            spaceBefore=10,
            spaceAfter=5,
            textColor=colors.HexColor("#333333"),
        ),
        "body": ParagraphStyle(
            "ATCBody",
            parent=base["BodyText"],
            fontName="Helvetica",
            fontSize=9.2,
            leading=12,
            spaceAfter=5,
            alignment=TA_LEFT,
        ),
        "list": ParagraphStyle(
            "ATCList",
            parent=base["BodyText"],
            fontName="Helvetica",
            fontSize=9.2,
            leading=12,
            leftIndent=12,
            firstLineIndent=-8,
            spaceAfter=3,
        ),
        "code": ParagraphStyle(
            "ATCCode",
            parent=base["Code"],
            fontName="Courier",
            fontSize=7.8,
            leading=9.5,
            leftIndent=6,
            rightIndent=6,
            backColor=colors.HexColor("#F4F4F4"),
            borderColor=colors.HexColor("#DDDDDD"),
            borderWidth=0.3,
            borderPadding=4,
            spaceBefore=4,
            spaceAfter=7,
        ),
    }


def flush_paragraph(story, lines, styles):
    if not lines:
        return
    paragraph = " ".join(line.strip() for line in lines if line.strip())
    if paragraph:
        story.append(Paragraph(normalize_inline_markdown(paragraph), styles["body"]))
    lines.clear()


def markdown_to_story(markdown: str, title: str):
    styles = build_styles()
    story = [Paragraph(escape_text(title), styles["title"]), Spacer(1, 4 * mm)]
    paragraph_lines: list[str] = []
    code_lines: list[str] = []
    in_code = False

    for raw_line in markdown.splitlines():
        line = raw_line.rstrip()
        if line.startswith("```"):
            if in_code:
                story.append(Preformatted("\n".join(code_lines), styles["code"]))
                code_lines.clear()
                in_code = False
            else:
                flush_paragraph(story, paragraph_lines, styles)
                in_code = True
            continue

        if in_code:
            code_lines.append(line)
            continue

        if not line.strip():
            flush_paragraph(story, paragraph_lines, styles)
            continue

        heading = re.match(r"^(#{1,6})\s+(.*)$", line)
        if heading:
            flush_paragraph(story, paragraph_lines, styles)
            level = len(heading.group(1))
            style = styles["h1"] if level <= 2 else styles["h2"]
            story.append(Paragraph(normalize_inline_markdown(heading.group(2)), style))
            continue

        list_item = re.match(r"^\s*[-*]\s+(.*)$", line)
        if list_item:
            flush_paragraph(story, paragraph_lines, styles)
            story.append(Paragraph("- " + normalize_inline_markdown(list_item.group(1)), styles["list"]))
            continue

        paragraph_lines.append(line)

    flush_paragraph(story, paragraph_lines, styles)
    if code_lines:
        story.append(Preformatted("\n".join(code_lines), styles["code"]))
    return story


def add_page_number(canvas, doc):
    canvas.saveState()
    canvas.setFont("Helvetica", 8)
    canvas.setFillColor(colors.grey)
    canvas.drawRightString(200 * mm, 10 * mm, f"Page {doc.page}")
    canvas.restoreState()


def build_pdf(source: Path, target: Path, title: str) -> None:
    markdown = source.read_text(encoding="utf-8")
    target.parent.mkdir(parents=True, exist_ok=True)
    doc = SimpleDocTemplate(
        str(target),
        pagesize=A4,
        rightMargin=16 * mm,
        leftMargin=16 * mm,
        topMargin=16 * mm,
        bottomMargin=16 * mm,
        title=title,
        author="Renato Alexandre dos Santos Freitas",
        subject="Advanced Trigonometry Calculator documentation",
    )
    story = markdown_to_story(markdown, title)
    doc.build(story, onFirstPage=add_page_number, onLaterPages=add_page_number)


def main() -> int:
    parser = argparse.ArgumentParser(description="Build ATC documentation PDFs.")
    parser.add_argument("--check", action="store_true", help="Only check that expected PDFs exist.")
    args = parser.parse_args()

    if args.check:
        missing = [target for _, target, _ in DOCUMENTS if not (ROOT / target).exists()]
        if missing:
            for target in missing:
                print(f"missing: {target}")
            return 1
        print("All documentation PDFs exist.")
        return 0

    for source_rel, target_rel, title in DOCUMENTS:
        source = ROOT / source_rel
        target = ROOT / target_rel
        build_pdf(source, target, title)
        print(f"built {target_rel}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
