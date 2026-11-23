# MP3 Tag Reader and Editor

A command-line tool written in C that reads and edits ID3v2 metadata in MP3 files, using only the standard C library.

## Features

- **View** the title, artist, album/movie, year, language and comments of an MP3 file
- **Edit** any one of these fields directly from the command line
- Built-in `-h` help option
- Input validation for arguments and missing files
- Safe editing: changes are written to a temp file first, so the original is never half-overwritten

## Usage

### Compile

```bash
gcc main.c view.c edit.c -o a.out
```

### Commands

| Action | Command |
|---|---|
| View tag | `./a.out -v filename.mp3` |
| Edit title | `./a.out -e -t "New Title" filename.mp3` |
| Edit artist | `./a.out -e -a "New Artist" filename.mp3` |
| Edit movie/album | `./a.out -e -m "New Movie" filename.mp3` |
| Edit year | `./a.out -e -y 2024 filename.mp3` |
| Edit language | `./a.out -e -l "Telugu" filename.mp3` |
| Edit comments | `./a.out -e -c "New comment" filename.mp3` |
| Help | `./a.out -h` |

### Example


<img width="732" height="127" alt="image" src="https://github.com/user-attachments/assets/8ef5f01a-2299-4f3b-9585-dd13a33a16e6" />


## How It Works

An MP3 file starts with a 10-byte ID3v2 header (`"ID3"`, version, flags, tag size), followed by frames. Each frame contains a 4-character ID (e.g. `TIT2` for title), a 4-byte big-endian size, 2 flag bytes, 1 encoding byte and the data.

| Frame ID | Field |
|---|---|
| `TIT2` | Title |
| `TPE1` | Artist |
| `TALB` | Album / Movie |
| `TYER` | Year |
| `TCON` | Language / Genre |
| `COMM` | Comments |

### View

The program skips the header, reads each frame, converts the frame size from big-endian using `swap()`, and stores the data in an `MP3tag` structure. For `COMM` frames it skips the 3-byte language code and the short description before copying the comment text.

### Edit

Because a new value can have a different length, the file can't be edited in place. The program:

1. Copies the header to a temp file
2. Rewrites the target frame with the new value and size
3. Copies the other frames unchanged
4. Updates the syncsafe tag size in the header
5. Copies the remaining data (audio) in 4 KB chunks
6. Replaces the original file with the temp file

## Concepts Practiced

- Binary file I/O (`fread`, `fwrite`, `fseek`, `ftell`)
- Big-endian vs little-endian byte order
- Syncsafe integers and bit manipulation
- Command-line arguments (`argc`, `argv`)
- Modular programming with header files
- Safe file editing with a temp file

## Limitations

- Reads only the first 6 frames, in a fixed order
- Uses fixed-size 100-byte buffers
- Supports text frames in ISO-8859-1/UTF-8 only (no UTF-16)
- Targets ID3v2.3; ID3v2.4 is not fully supported

## Future Improvements

- Read frames until padding instead of a fixed count
- Dynamic memory allocation for frame data
- UTF-16 support
- ID3v2.4 support
- Check every `fread`/`fwrite` return value

## Author

**Vinay Rohan S**
