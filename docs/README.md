# Advanced Trigonometry Calculator Documentation

This folder contains editable Markdown documentation and generated PDF files
for Advanced Trigonometry Calculator (ATC).

## Language Structure

- `docs/en/`: English documentation. English is the reference language for
  open-source and community-facing documents.
- `docs/pt-PT/`: Portuguese documentation maintained for the
  Portuguese-speaking community.
- `docs/pdf/`: generated PDF versions of the main documents.
- `docs/docx/`: editable DOCX versions of the full user guides.

The root Markdown files in `docs/` are kept for compatibility with existing
links. They should remain aligned with the English versions in `docs/en/`.

## Synchronization Note

Whenever a document is changed in one language, check whether the corresponding
document in the other language also needs to be updated.

After relevant Markdown changes, regenerate the PDF versions in `docs/pdf/`.

## Regenerating PDFs

The repository includes a Python-based PDF generation helper:

```powershell
.\.venv-docs\Scripts\python.exe .\tools\docs\build_pdfs.py
```

Editable DOCX full user guides can be regenerated with:

```powershell
.\.venv-docs\Scripts\python.exe .\tools\docs\build_docx.py
```

To recreate the local documentation environment:

```powershell
python -m venv .venv-docs
.\.venv-docs\Scripts\python.exe -m pip install -r .\tools\docs\requirements.txt
.\.venv-docs\Scripts\python.exe .\tools\docs\build_pdfs.py
.\.venv-docs\Scripts\python.exe .\tools\docs\build_docx.py
```

The `.venv-docs` folder is local tooling state and is intentionally ignored by
Git.

## Main Documents

English:

- [User Guide](en/User_Guide.md)
- [Full User Guide](en/User_Guide_Full.md)
- [Developer Guide](en/Developer_Guide.md)
- [Architecture](en/Architecture.md)
- [Testing](en/Testing.md)
- [Release Notes 2.1.7](en/RELEASE_2.1.7.md)
- [Technical Documentation 2.1.7](en/ATC_2.1.7_DOCUMENTATION.md)

Portuguese:

- [Guia de Utilizador](pt-PT/User_Guide.md)
- [Guia Completo de Utilizador](pt-PT/User_Guide_Full.md)
- [Guia de Developer](pt-PT/Developer_Guide.md)
- [Arquitetura](pt-PT/Architecture.md)
- [Testes](pt-PT/Testing.md)
- [Notas de Release 2.1.7](pt-PT/RELEASE_2.1.7.md)
- [Documentacao Tecnica 2.1.7](pt-PT/ATC_2.1.7_DOCUMENTATION.md)

PDF:

- [ATC_User_Guide_EN.pdf](pdf/ATC_User_Guide_EN.pdf)
- [ATC_User_Guide_PT-PT.pdf](pdf/ATC_User_Guide_PT-PT.pdf)
- [ATC_Full_User_Guide_EN.pdf](pdf/ATC_Full_User_Guide_EN.pdf)
- [ATC_Full_User_Guide_PT-PT.pdf](pdf/ATC_Full_User_Guide_PT-PT.pdf)
- [ATC_Full_User_Guide_EN.docx](docx/ATC_Full_User_Guide_EN.docx)
- [ATC_Full_User_Guide_PT-PT.docx](docx/ATC_Full_User_Guide_PT-PT.docx)
- [ATC_Developer_Guide_EN.pdf](pdf/ATC_Developer_Guide_EN.pdf)
- [ATC_Developer_Guide_PT-PT.pdf](pdf/ATC_Developer_Guide_PT-PT.pdf)
- [ATC_Architecture_EN.pdf](pdf/ATC_Architecture_EN.pdf)
- [ATC_Architecture_PT-PT.pdf](pdf/ATC_Architecture_PT-PT.pdf)
- [ATC_Testing_EN.pdf](pdf/ATC_Testing_EN.pdf)
- [ATC_Testing_PT-PT.pdf](pdf/ATC_Testing_PT-PT.pdf)
- [ATC_Release_2.1.7_EN.pdf](pdf/ATC_Release_2.1.7_EN.pdf)
- [ATC_Release_2.1.7_PT-PT.pdf](pdf/ATC_Release_2.1.7_PT-PT.pdf)
