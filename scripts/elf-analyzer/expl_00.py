"""
Explore ELF files with pyelftools.
Based on https://medium.com/analytics-vidhya/exploring-elf-files-using-pyelftools-93bb7665cce3

https://github.com/eliben/pyelftools
https://github.com/eliben/pyelftools/wiki/User's-guide


https://docs.oracle.com/cd/E37838_01/html/E61063/elf-23207.html
"""
# Standard library imports
import pathlib
# Third party imports

# import elftools
import elftools.elf.elffile
# Local application/library imports


# ELF_PATH = pathlib.PosixPath("/home/boris/projects/emb1.wt0/bin/stm32f051_sbx.elf")
ELF_PATH = pathlib.PosixPath("/home/boris/projects/emb1.wt0/bin/stm32h743_sbx.elf")


if __name__ == '__main__':

    # print(f"{elftools.__file__}")

    with open(ELF_PATH, 'rb') as bin_file:
        elf_file = elftools.elf.elffile.ELFFile(bin_file)
        # Segments = headers
        # Each segment contains one (zero?) or more sections

        segments: list[dict] = []
        for segment_idx in range(elf_file.num_segments()):
            segments.insert(segment_idx, dict())
            segments[segment_idx]['segment'] = elf_file.get_segment(segment_idx)
            segments[segment_idx]['sections'] = list()

        sections_other = []
        for section_idx in range(elf_file.num_sections()):
            section = elf_file.get_section(section_idx)
            for segment in segments:
                if segment['segment'].section_in_segment(section):
                    segment['sections'].append(section)
                    break
            else:
                sections_other.append(section)

        for i, segment in enumerate(segments):
            seg_head = segment['segment'].header
            print(f"Segment {i}:")
            print(f"\tType: {seg_head.p_type}\n"
                  f"\tOffset: {hex(seg_head.p_offset)}\n"
                  f"\tVirtual address: {hex(seg_head.p_vaddr)}\n"
                  f"\tPhysical address: {(seg_head.p_paddr)}\n"
                  f"\tSize in file: {hex(seg_head.p_filesz)}\n"
                  f"\tSize in memory: {hex(seg_head.p_memsz)}")
            if segment['sections']:
                print("\tSections:")
                for section in segment['sections']:
                    sh_addr = section['sh_addr']
                    sh_size = section['sh_size']
                    sh_type = section['sh_type']
                    print(f"\t\t{section.name}, addr={hex(sh_addr)}, size={sh_size}, type={sh_type}, {type(section)}")
            else:
                print('\tSegment contains no sections')

        if sections_other:
            print('Other sections:')
            for section in sections_other:
                sh_addr = section['sh_addr']
                sh_size = section['sh_size']
                sh_type = section['sh_type']
                print(f"\t{section.name}, addr={hex(sh_addr)}, size={sh_size}, type={sh_type}, {type(section)}")
                if type(section) == elftools.elf.sections.SymbolTableSection:
                    print(f"\t\t{section.num_symbols()} symbols")
                    for symbol in section.iter_symbols():
                        print(f"\t\t\t{symbol.name}:")
                        for k, v in symbol.entry.items():
                            if k in {"st_value"}:
                                v_str = hex(v)
                            else:
                                v_str = str(v)
                            print(f"\t\t\t\t{k}: {v_str}")
