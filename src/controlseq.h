#include "xtermcontrol.h"

#ifndef CONTROLSEQ_H
#define CONTROLSEQ_H

struct controlseq ctlseqstab[] =
    {
        {10, 0, NULL, OSC, /* FG */
         "foreground",
         "--fg=COLOR",
         "set foreground color"},

        {11, 0, NULL, OSC, /* BG */
         "background",
         "--bg=COLOR",
         "set background color"},

        {4, 0, NULL, OSC, /* COLOR_0 */
         "color0",
         "--colorN=COLOR",
         "set N'th [0-255] color, e.g. --color88=COLOR"},

        {4, 1, NULL, OSC, /* COLOR_1 */
         "color1",
         NULL, NULL},

        {4, 2, NULL, OSC, /* COLOR_2 */
         "color2",
         NULL, NULL},

        {4, 3, NULL, OSC, /* COLOR_3 */
         "color3",
         NULL, NULL},

        {4, 4, NULL, OSC, /* COLOR_4 */
         "color4",
         NULL, NULL},

        {4, 5, NULL, OSC, /* COLOR_5 */
         "color5",
         NULL, NULL},

        {4, 6, NULL, OSC, /* COLOR_6 */
         "color6",
         NULL, NULL},

        {4, 7, NULL, OSC, /* COLOR_7 */
         "color7",
         NULL, NULL},

        {4, 8, NULL, OSC, /* COLOR_8 */
         "color8",
         NULL, NULL},

        {4, 9, NULL, OSC, /* COLOR_9 */
         "color9",
         NULL, NULL},

        {4, 10, NULL, OSC, /* COLOR_10 */
         "color10",
         NULL, NULL},

        {4, 11, NULL, OSC, /* COLOR_11 */
         "color11",
         NULL, NULL},

        {4, 12, NULL, OSC, /* COLOR_12 */
         "color12",
         NULL, NULL},

        {4, 13, NULL, OSC, /* COLOR_13 */
         "color13",
         NULL, NULL},

        {4, 14, NULL, OSC, /* COLOR_14 */
         "color14",
         NULL, NULL},

        {4, 15, NULL, OSC, /* COLOR_15 */
         "color15",
         NULL, NULL},

        {4, 16, NULL, OSC, /* COLOR_16 */
         "color16",
         NULL, NULL},

        {4, 17, NULL, OSC, /* COLOR_17 */
         "color17",
         NULL, NULL},

        {4, 18, NULL, OSC, /* COLOR_18 */
         "color18",
         NULL, NULL},

        {4, 19, NULL, OSC, /* COLOR_19 */
         "color19",
         NULL, NULL},

        {4, 20, NULL, OSC, /* COLOR_20 */
         "color20",
         NULL, NULL},

        {4, 21, NULL, OSC, /* COLOR_21 */
         "color21",
         NULL, NULL},

        {4, 22, NULL, OSC, /* COLOR_22 */
         "color22",
         NULL, NULL},

        {4, 23, NULL, OSC, /* COLOR_23 */
         "color23",
         NULL, NULL},

        {4, 24, NULL, OSC, /* COLOR_24 */
         "color24",
         NULL, NULL},

        {4, 25, NULL, OSC, /* COLOR_25 */
         "color25",
         NULL, NULL},

        {4, 26, NULL, OSC, /* COLOR_26 */
         "color26",
         NULL, NULL},

        {4, 27, NULL, OSC, /* COLOR_27 */
         "color27",
         NULL, NULL},

        {4, 28, NULL, OSC, /* COLOR_28 */
         "color28",
         NULL, NULL},

        {4, 29, NULL, OSC, /* COLOR_29 */
         "color29",
         NULL, NULL},

        {4, 30, NULL, OSC, /* COLOR_30 */
         "color30",
         NULL, NULL},

        {4, 31, NULL, OSC, /* COLOR_31 */
         "color31",
         NULL, NULL},

        {4, 32, NULL, OSC, /* COLOR_32 */
         "color32",
         NULL, NULL},

        {4, 33, NULL, OSC, /* COLOR_33 */
         "color33",
         NULL, NULL},

        {4, 34, NULL, OSC, /* COLOR_34 */
         "color34",
         NULL, NULL},

        {4, 35, NULL, OSC, /* COLOR_35 */
         "color35",
         NULL, NULL},

        {4, 36, NULL, OSC, /* COLOR_36 */
         "color36",
         NULL, NULL},

        {4, 37, NULL, OSC, /* COLOR_37 */
         "color37",
         NULL, NULL},

        {4, 38, NULL, OSC, /* COLOR_38 */
         "color38",
         NULL, NULL},

        {4, 39, NULL, OSC, /* COLOR_39 */
         "color39",
         NULL, NULL},

        {4, 40, NULL, OSC, /* COLOR_40 */
         "color40",
         NULL, NULL},

        {4, 41, NULL, OSC, /* COLOR_41 */
         "color41",
         NULL, NULL},

        {4, 42, NULL, OSC, /* COLOR_42 */
         "color42",
         NULL, NULL},

        {4, 43, NULL, OSC, /* COLOR_43 */
         "color43",
         NULL, NULL},

        {4, 44, NULL, OSC, /* COLOR_44 */
         "color44",
         NULL, NULL},

        {4, 45, NULL, OSC, /* COLOR_45 */
         "color45",
         NULL, NULL},

        {4, 46, NULL, OSC, /* COLOR_46 */
         "color46",
         NULL, NULL},

        {4, 47, NULL, OSC, /* COLOR_47 */
         "color47",
         NULL, NULL},

        {4, 48, NULL, OSC, /* COLOR_48 */
         "color48",
         NULL, NULL},

        {4, 49, NULL, OSC, /* COLOR_49 */
         "color49",
         NULL, NULL},

        {4, 50, NULL, OSC, /* COLOR_50 */
         "color50",
         NULL, NULL},

        {4, 51, NULL, OSC, /* COLOR_51 */
         "color51",
         NULL, NULL},

        {4, 52, NULL, OSC, /* COLOR_52 */
         "color52",
         NULL, NULL},

        {4, 53, NULL, OSC, /* COLOR_53 */
         "color53",
         NULL, NULL},

        {4, 54, NULL, OSC, /* COLOR_54 */
         "color54",
         NULL, NULL},

        {4, 55, NULL, OSC, /* COLOR_55 */
         "color55",
         NULL, NULL},

        {4, 56, NULL, OSC, /* COLOR_56 */
         "color56",
         NULL, NULL},

        {4, 57, NULL, OSC, /* COLOR_57 */
         "color57",
         NULL, NULL},

        {4, 58, NULL, OSC, /* COLOR_58 */
         "color58",
         NULL, NULL},

        {4, 59, NULL, OSC, /* COLOR_59 */
         "color59",
         NULL, NULL},

        {4, 60, NULL, OSC, /* COLOR_60 */
         "color60",
         NULL, NULL},

        {4, 61, NULL, OSC, /* COLOR_61 */
         "color61",
         NULL, NULL},

        {4, 62, NULL, OSC, /* COLOR_62 */
         "color62",
         NULL, NULL},

        {4, 63, NULL, OSC, /* COLOR_63 */
         "color63",
         NULL, NULL},

        {4, 64, NULL, OSC, /* COLOR_64 */
         "color64",
         NULL, NULL},

        {4, 65, NULL, OSC, /* COLOR_65 */
         "color65",
         NULL, NULL},

        {4, 66, NULL, OSC, /* COLOR_66 */
         "color66",
         NULL, NULL},

        {4, 67, NULL, OSC, /* COLOR_67 */
         "color67",
         NULL, NULL},

        {4, 68, NULL, OSC, /* COLOR_68 */
         "color68",
         NULL, NULL},

        {4, 69, NULL, OSC, /* COLOR_69 */
         "color69",
         NULL, NULL},

        {4, 70, NULL, OSC, /* COLOR_70 */
         "color70",
         NULL, NULL},

        {4, 71, NULL, OSC, /* COLOR_71 */
         "color71",
         NULL, NULL},

        {4, 72, NULL, OSC, /* COLOR_72 */
         "color72",
         NULL, NULL},

        {4, 73, NULL, OSC, /* COLOR_73 */
         "color73",
         NULL, NULL},

        {4, 74, NULL, OSC, /* COLOR_74 */
         "color74",
         NULL, NULL},

        {4, 75, NULL, OSC, /* COLOR_75 */
         "color75",
         NULL, NULL},

        {4, 76, NULL, OSC, /* COLOR_76 */
         "color76",
         NULL, NULL},

        {4, 77, NULL, OSC, /* COLOR_77 */
         "color77",
         NULL, NULL},

        {4, 78, NULL, OSC, /* COLOR_78 */
         "color78",
         NULL, NULL},

        {4, 79, NULL, OSC, /* COLOR_79 */
         "color79",
         NULL, NULL},

        {4, 80, NULL, OSC, /* COLOR_80 */
         "color80",
         NULL, NULL},

        {4, 81, NULL, OSC, /* COLOR_81 */
         "color81",
         NULL, NULL},

        {4, 82, NULL, OSC, /* COLOR_82 */
         "color82",
         NULL, NULL},

        {4, 83, NULL, OSC, /* COLOR_83 */
         "color83",
         NULL, NULL},

        {4, 84, NULL, OSC, /* COLOR_84 */
         "color84",
         NULL, NULL},

        {4, 85, NULL, OSC, /* COLOR_85 */
         "color85",
         NULL, NULL},

        {4, 86, NULL, OSC, /* COLOR_86 */
         "color86",
         NULL, NULL},

        {4, 87, NULL, OSC, /* COLOR_87 */
         "color87",
         NULL, NULL},

        {4, 88, NULL, OSC, /* COLOR_88 */
         "color88",
         NULL, NULL},

        {4, 89, NULL, OSC, /* COLOR_89 */
         "color89",
         NULL, NULL},

        {4, 90, NULL, OSC, /* COLOR_90 */
         "color90",
         NULL, NULL},

        {4, 91, NULL, OSC, /* COLOR_91 */
         "color91",
         NULL, NULL},

        {4, 92, NULL, OSC, /* COLOR_92 */
         "color92",
         NULL, NULL},

        {4, 93, NULL, OSC, /* COLOR_93 */
         "color93",
         NULL, NULL},

        {4, 94, NULL, OSC, /* COLOR_94 */
         "color94",
         NULL, NULL},

        {4, 95, NULL, OSC, /* COLOR_95 */
         "color95",
         NULL, NULL},

        {4, 96, NULL, OSC, /* COLOR_96 */
         "color96",
         NULL, NULL},

        {4, 97, NULL, OSC, /* COLOR_97 */
         "color97",
         NULL, NULL},

        {4, 98, NULL, OSC, /* COLOR_98 */
         "color98",
         NULL, NULL},

        {4, 99, NULL, OSC, /* COLOR_99 */
         "color99",
         NULL, NULL},

        {4, 100, NULL, OSC, /* COLOR_100 */
         "color100",
         NULL, NULL},

        {4, 101, NULL, OSC, /* COLOR_101 */
         "color101",
         NULL, NULL},

        {4, 102, NULL, OSC, /* COLOR_102 */
         "color102",
         NULL, NULL},

        {4, 103, NULL, OSC, /* COLOR_103 */
         "color103",
         NULL, NULL},

        {4, 104, NULL, OSC, /* COLOR_104 */
         "color104",
         NULL, NULL},

        {4, 105, NULL, OSC, /* COLOR_105 */
         "color105",
         NULL, NULL},

        {4, 106, NULL, OSC, /* COLOR_106 */
         "color106",
         NULL, NULL},

        {4, 107, NULL, OSC, /* COLOR_107 */
         "color107",
         NULL, NULL},

        {4, 108, NULL, OSC, /* COLOR_108 */
         "color108",
         NULL, NULL},

        {4, 109, NULL, OSC, /* COLOR_109 */
         "color109",
         NULL, NULL},

        {4, 110, NULL, OSC, /* COLOR_110 */
         "color110",
         NULL, NULL},

        {4, 111, NULL, OSC, /* COLOR_111 */
         "color111",
         NULL, NULL},

        {4, 112, NULL, OSC, /* COLOR_112 */
         "color112",
         NULL, NULL},

        {4, 113, NULL, OSC, /* COLOR_113 */
         "color113",
         NULL, NULL},

        {4, 114, NULL, OSC, /* COLOR_114 */
         "color114",
         NULL, NULL},

        {4, 115, NULL, OSC, /* COLOR_115 */
         "color115",
         NULL, NULL},

        {4, 116, NULL, OSC, /* COLOR_116 */
         "color116",
         NULL, NULL},

        {4, 117, NULL, OSC, /* COLOR_117 */
         "color117",
         NULL, NULL},

        {4, 118, NULL, OSC, /* COLOR_118 */
         "color118",
         NULL, NULL},

        {4, 119, NULL, OSC, /* COLOR_119 */
         "color119",
         NULL, NULL},

        {4, 120, NULL, OSC, /* COLOR_120 */
         "color120",
         NULL, NULL},

        {4, 121, NULL, OSC, /* COLOR_121 */
         "color121",
         NULL, NULL},

        {4, 122, NULL, OSC, /* COLOR_122 */
         "color122",
         NULL, NULL},

        {4, 123, NULL, OSC, /* COLOR_123 */
         "color123",
         NULL, NULL},

        {4, 124, NULL, OSC, /* COLOR_124 */
         "color124",
         NULL, NULL},

        {4, 125, NULL, OSC, /* COLOR_125 */
         "color125",
         NULL, NULL},

        {4, 126, NULL, OSC, /* COLOR_126 */
         "color126",
         NULL, NULL},

        {4, 127, NULL, OSC, /* COLOR_127 */
         "color127",
         NULL, NULL},

        {4, 128, NULL, OSC, /* COLOR_128 */
         "color128",
         NULL, NULL},

        {4, 129, NULL, OSC, /* COLOR_129 */
         "color129",
         NULL, NULL},

        {4, 130, NULL, OSC, /* COLOR_130 */
         "color130",
         NULL, NULL},

        {4, 131, NULL, OSC, /* COLOR_131 */
         "color131",
         NULL, NULL},

        {4, 132, NULL, OSC, /* COLOR_132 */
         "color132",
         NULL, NULL},

        {4, 133, NULL, OSC, /* COLOR_133 */
         "color133",
         NULL, NULL},

        {4, 134, NULL, OSC, /* COLOR_134 */
         "color134",
         NULL, NULL},

        {4, 135, NULL, OSC, /* COLOR_135 */
         "color135",
         NULL, NULL},

        {4, 136, NULL, OSC, /* COLOR_136 */
         "color136",
         NULL, NULL},

        {4, 137, NULL, OSC, /* COLOR_137 */
         "color137",
         NULL, NULL},

        {4, 138, NULL, OSC, /* COLOR_138 */
         "color138",
         NULL, NULL},

        {4, 139, NULL, OSC, /* COLOR_139 */
         "color139",
         NULL, NULL},

        {4, 140, NULL, OSC, /* COLOR_140 */
         "color140",
         NULL, NULL},

        {4, 141, NULL, OSC, /* COLOR_141 */
         "color141",
         NULL, NULL},

        {4, 142, NULL, OSC, /* COLOR_142 */
         "color142",
         NULL, NULL},

        {4, 143, NULL, OSC, /* COLOR_143 */
         "color143",
         NULL, NULL},

        {4, 144, NULL, OSC, /* COLOR_144 */
         "color144",
         NULL, NULL},

        {4, 145, NULL, OSC, /* COLOR_145 */
         "color145",
         NULL, NULL},

        {4, 146, NULL, OSC, /* COLOR_146 */
         "color146",
         NULL, NULL},

        {4, 147, NULL, OSC, /* COLOR_147 */
         "color147",
         NULL, NULL},

        {4, 148, NULL, OSC, /* COLOR_148 */
         "color148",
         NULL, NULL},

        {4, 149, NULL, OSC, /* COLOR_149 */
         "color149",
         NULL, NULL},

        {4, 150, NULL, OSC, /* COLOR_150 */
         "color150",
         NULL, NULL},

        {4, 151, NULL, OSC, /* COLOR_151 */
         "color151",
         NULL, NULL},

        {4, 152, NULL, OSC, /* COLOR_152 */
         "color152",
         NULL, NULL},

        {4, 153, NULL, OSC, /* COLOR_153 */
         "color153",
         NULL, NULL},

        {4, 154, NULL, OSC, /* COLOR_154 */
         "color154",
         NULL, NULL},

        {4, 155, NULL, OSC, /* COLOR_155 */
         "color155",
         NULL, NULL},

        {4, 156, NULL, OSC, /* COLOR_156 */
         "color156",
         NULL, NULL},

        {4, 157, NULL, OSC, /* COLOR_157 */
         "color157",
         NULL, NULL},

        {4, 158, NULL, OSC, /* COLOR_158 */
         "color158",
         NULL, NULL},

        {4, 159, NULL, OSC, /* COLOR_159 */
         "color159",
         NULL, NULL},

        {4, 160, NULL, OSC, /* COLOR_160 */
         "color160",
         NULL, NULL},

        {4, 161, NULL, OSC, /* COLOR_161 */
         "color161",
         NULL, NULL},

        {4, 162, NULL, OSC, /* COLOR_162 */
         "color162",
         NULL, NULL},

        {4, 163, NULL, OSC, /* COLOR_163 */
         "color163",
         NULL, NULL},

        {4, 164, NULL, OSC, /* COLOR_164 */
         "color164",
         NULL, NULL},

        {4, 165, NULL, OSC, /* COLOR_165 */
         "color165",
         NULL, NULL},

        {4, 166, NULL, OSC, /* COLOR_166 */
         "color166",
         NULL, NULL},

        {4, 167, NULL, OSC, /* COLOR_167 */
         "color167",
         NULL, NULL},

        {4, 168, NULL, OSC, /* COLOR_168 */
         "color168",
         NULL, NULL},

        {4, 169, NULL, OSC, /* COLOR_169 */
         "color169",
         NULL, NULL},

        {4, 170, NULL, OSC, /* COLOR_170 */
         "color170",
         NULL, NULL},

        {4, 171, NULL, OSC, /* COLOR_171 */
         "color171",
         NULL, NULL},

        {4, 172, NULL, OSC, /* COLOR_172 */
         "color172",
         NULL, NULL},

        {4, 173, NULL, OSC, /* COLOR_173 */
         "color173",
         NULL, NULL},

        {4, 174, NULL, OSC, /* COLOR_174 */
         "color174",
         NULL, NULL},

        {4, 175, NULL, OSC, /* COLOR_175 */
         "color175",
         NULL, NULL},

        {4, 176, NULL, OSC, /* COLOR_176 */
         "color176",
         NULL, NULL},

        {4, 177, NULL, OSC, /* COLOR_177 */
         "color177",
         NULL, NULL},

        {4, 178, NULL, OSC, /* COLOR_178 */
         "color178",
         NULL, NULL},

        {4, 179, NULL, OSC, /* COLOR_179 */
         "color179",
         NULL, NULL},

        {4, 180, NULL, OSC, /* COLOR_180 */
         "color180",
         NULL, NULL},

        {4, 181, NULL, OSC, /* COLOR_181 */
         "color181",
         NULL, NULL},

        {4, 182, NULL, OSC, /* COLOR_182 */
         "color182",
         NULL, NULL},

        {4, 183, NULL, OSC, /* COLOR_183 */
         "color183",
         NULL, NULL},

        {4, 184, NULL, OSC, /* COLOR_184 */
         "color184",
         NULL, NULL},

        {4, 185, NULL, OSC, /* COLOR_185 */
         "color185",
         NULL, NULL},

        {4, 186, NULL, OSC, /* COLOR_186 */
         "color186",
         NULL, NULL},

        {4, 187, NULL, OSC, /* COLOR_187 */
         "color187",
         NULL, NULL},

        {4, 188, NULL, OSC, /* COLOR_188 */
         "color188",
         NULL, NULL},

        {4, 189, NULL, OSC, /* COLOR_189 */
         "color189",
         NULL, NULL},

        {4, 190, NULL, OSC, /* COLOR_190 */
         "color190",
         NULL, NULL},

        {4, 191, NULL, OSC, /* COLOR_191 */
         "color191",
         NULL, NULL},

        {4, 192, NULL, OSC, /* COLOR_192 */
         "color192",
         NULL, NULL},

        {4, 193, NULL, OSC, /* COLOR_193 */
         "color193",
         NULL, NULL},

        {4, 194, NULL, OSC, /* COLOR_194 */
         "color194",
         NULL, NULL},

        {4, 195, NULL, OSC, /* COLOR_195 */
         "color195",
         NULL, NULL},

        {4, 196, NULL, OSC, /* COLOR_196 */
         "color196",
         NULL, NULL},

        {4, 197, NULL, OSC, /* COLOR_197 */
         "color197",
         NULL, NULL},

        {4, 198, NULL, OSC, /* COLOR_198 */
         "color198",
         NULL, NULL},

        {4, 199, NULL, OSC, /* COLOR_199 */
         "color199",
         NULL, NULL},

        {4, 200, NULL, OSC, /* COLOR_200 */
         "color200",
         NULL, NULL},

        {4, 201, NULL, OSC, /* COLOR_201 */
         "color201",
         NULL, NULL},

        {4, 202, NULL, OSC, /* COLOR_202 */
         "color202",
         NULL, NULL},

        {4, 203, NULL, OSC, /* COLOR_203 */
         "color203",
         NULL, NULL},

        {4, 204, NULL, OSC, /* COLOR_204 */
         "color204",
         NULL, NULL},

        {4, 205, NULL, OSC, /* COLOR_205 */
         "color205",
         NULL, NULL},

        {4, 206, NULL, OSC, /* COLOR_206 */
         "color206",
         NULL, NULL},

        {4, 207, NULL, OSC, /* COLOR_207 */
         "color207",
         NULL, NULL},

        {4, 208, NULL, OSC, /* COLOR_208 */
         "color208",
         NULL, NULL},

        {4, 209, NULL, OSC, /* COLOR_209 */
         "color209",
         NULL, NULL},

        {4, 210, NULL, OSC, /* COLOR_210 */
         "color210",
         NULL, NULL},

        {4, 211, NULL, OSC, /* COLOR_211 */
         "color211",
         NULL, NULL},

        {4, 212, NULL, OSC, /* COLOR_212 */
         "color212",
         NULL, NULL},

        {4, 213, NULL, OSC, /* COLOR_213 */
         "color213",
         NULL, NULL},

        {4, 214, NULL, OSC, /* COLOR_214 */
         "color214",
         NULL, NULL},

        {4, 215, NULL, OSC, /* COLOR_215 */
         "color215",
         NULL, NULL},

        {4, 216, NULL, OSC, /* COLOR_216 */
         "color216",
         NULL, NULL},

        {4, 217, NULL, OSC, /* COLOR_217 */
         "color217",
         NULL, NULL},

        {4, 218, NULL, OSC, /* COLOR_218 */
         "color218",
         NULL, NULL},

        {4, 219, NULL, OSC, /* COLOR_219 */
         "color219",
         NULL, NULL},

        {4, 220, NULL, OSC, /* COLOR_220 */
         "color220",
         NULL, NULL},

        {4, 221, NULL, OSC, /* COLOR_221 */
         "color221",
         NULL, NULL},

        {4, 222, NULL, OSC, /* COLOR_222 */
         "color222",
         NULL, NULL},

        {4, 223, NULL, OSC, /* COLOR_223 */
         "color223",
         NULL, NULL},

        {4, 224, NULL, OSC, /* COLOR_224 */
         "color224",
         NULL, NULL},

        {4, 225, NULL, OSC, /* COLOR_225 */
         "color225",
         NULL, NULL},

        {4, 226, NULL, OSC, /* COLOR_226 */
         "color226",
         NULL, NULL},

        {4, 227, NULL, OSC, /* COLOR_227 */
         "color227",
         NULL, NULL},

        {4, 228, NULL, OSC, /* COLOR_228 */
         "color228",
         NULL, NULL},

        {4, 229, NULL, OSC, /* COLOR_229 */
         "color229",
         NULL, NULL},

        {4, 230, NULL, OSC, /* COLOR_230 */
         "color230",
         NULL, NULL},

        {4, 231, NULL, OSC, /* COLOR_231 */
         "color231",
         NULL, NULL},

        {4, 232, NULL, OSC, /* COLOR_232 */
         "color232",
         NULL, NULL},

        {4, 233, NULL, OSC, /* COLOR_233 */
         "color233",
         NULL, NULL},

        {4, 234, NULL, OSC, /* COLOR_234 */
         "color234",
         NULL, NULL},

        {4, 235, NULL, OSC, /* COLOR_235 */
         "color235",
         NULL, NULL},

        {4, 236, NULL, OSC, /* COLOR_236 */
         "color236",
         NULL, NULL},

        {4, 237, NULL, OSC, /* COLOR_237 */
         "color237",
         NULL, NULL},

        {4, 238, NULL, OSC, /* COLOR_238 */
         "color238",
         NULL, NULL},

        {4, 239, NULL, OSC, /* COLOR_239 */
         "color239",
         NULL, NULL},

        {4, 240, NULL, OSC, /* COLOR_240 */
         "color240",
         NULL, NULL},

        {4, 241, NULL, OSC, /* COLOR_241 */
         "color241",
         NULL, NULL},

        {4, 242, NULL, OSC, /* COLOR_242 */
         "color242",
         NULL, NULL},

        {4, 243, NULL, OSC, /* COLOR_243 */
         "color243",
         NULL, NULL},

        {4, 244, NULL, OSC, /* COLOR_244 */
         "color244",
         NULL, NULL},

        {4, 245, NULL, OSC, /* COLOR_245 */
         "color245",
         NULL, NULL},

        {4, 246, NULL, OSC, /* COLOR_246 */
         "color246",
         NULL, NULL},

        {4, 247, NULL, OSC, /* COLOR_247 */
         "color247",
         NULL, NULL},

        {4, 248, NULL, OSC, /* COLOR_248 */
         "color248",
         NULL, NULL},

        {4, 249, NULL, OSC, /* COLOR_249 */
         "color249",
         NULL, NULL},

        {4, 250, NULL, OSC, /* COLOR_250 */
         "color250",
         NULL, NULL},

        {4, 251, NULL, OSC, /* COLOR_251 */
         "color251",
         NULL, NULL},

        {4, 252, NULL, OSC, /* COLOR_252 */
         "color252",
         NULL, NULL},

        {4, 253, NULL, OSC, /* COLOR_253 */
         "color253",
         NULL, NULL},

        {4, 254, NULL, OSC, /* COLOR_254 */
         "color254",
         NULL, NULL},

        {4, 255, NULL, OSC, /* COLOR_255 */
         "color255",
         NULL, NULL},

        {17, 0, NULL, OSC, /* COLOR_HL */
         "highlight",
         "--highlight=COLOR",
         "set highlight color"},

        {12, 0, NULL, OSC, /* CURSOR */
         "cursor",
         "--cursor=COLOR",
         "set cursor color"},

        {13, 0, NULL, OSC, /* MOUSE_FG */
         "mouse-foreground",
         "--mouse-fg=COLOR",
         "set mouse pointer foreground color"},

        {14, 0, NULL, OSC, /* MOUSE_BG */
         "mouse-background",
         "--mouse-bg=COLOR",
         "set mouse pointer background color"},

        {50, 0, NULL, OSC, /* FONT */
         "font",
         "--font=FONT",
         "set font"},

        {0, 0, NULL, OSC, /* TITLE */
         "title",
         "--title=STRING",
         "set window title"},

        {8, 3, NULL, CSI, /* GEOMETRY */
         "geometry",
         "--geometry=WIDTHxHEIGHT+XOFF+YOFF",
         "set size and/or position"},

        {10, 0, NULL, GET_OSC, /* GET_FG */
         "foreground",
         "--get-fg",
         "report foreground color"},

        {11, 0, NULL, GET_OSC, /* GET_BG */
         "background",
         "--get-bg",
         "report background color"},

        {4, 0, NULL, GET_OSC, /* GET_COLOR_0 */
         "color0",
         "--get-colorN",
         "report N'th [0-255] color, e.g --get-color88"},

        {4, 1, NULL, GET_OSC, /* GET_COLOR_1 */
         "color1",
         NULL, NULL},

        {4, 2, NULL, GET_OSC, /* GET_COLOR_2 */
         "color2",
         NULL, NULL},

        {4, 3, NULL, GET_OSC, /* GET_COLOR_3 */
         "color3",
         NULL, NULL},

        {4, 4, NULL, GET_OSC, /* GET_COLOR_4 */
         "color4",
         NULL, NULL},

        {4, 5, NULL, GET_OSC, /* GET_COLOR_5 */
         "color5",
         NULL, NULL},

        {4, 6, NULL, GET_OSC, /* GET_COLOR_6 */
         "color6",
         NULL, NULL},

        {4, 7, NULL, GET_OSC, /* GET_COLOR_7 */
         "color7",
         NULL, NULL},

        {4, 8, NULL, GET_OSC, /* GET_COLOR_8 */
         "color8",
         NULL, NULL},

        {4, 9, NULL, GET_OSC, /* GET_COLOR_9 */
         "color9",
         NULL, NULL},

        {4, 10, NULL, GET_OSC, /* GET_COLOR_10 */
         "color10",
         NULL, NULL},

        {4, 11, NULL, GET_OSC, /* GET_COLOR_11 */
         "color11",
         NULL, NULL},

        {4, 12, NULL, GET_OSC, /* GET_COLOR_12 */
         "color12",
         NULL, NULL},

        {4, 13, NULL, GET_OSC, /* GET_COLOR_13 */
         "color13",
         NULL, NULL},

        {4, 14, NULL, GET_OSC, /* GET_COLOR_14 */
         "color14",
         NULL, NULL},

        {4, 15, NULL, GET_OSC, /* GET_COLOR_15 */
         "color15",
         NULL, NULL},

        {4, 16, NULL, GET_OSC, /* GET_COLOR_16 */
         "color16",
         NULL, NULL},

        {4, 17, NULL, GET_OSC, /* GET_COLOR_17 */
         "color17",
         NULL, NULL},

        {4, 18, NULL, GET_OSC, /* GET_COLOR_18 */
         "color18",
         NULL, NULL},

        {4, 19, NULL, GET_OSC, /* GET_COLOR_19 */
         "color19",
         NULL, NULL},

        {4, 20, NULL, GET_OSC, /* GET_COLOR_20 */
         "color20",
         NULL, NULL},

        {4, 21, NULL, GET_OSC, /* GET_COLOR_21 */
         "color21",
         NULL, NULL},

        {4, 22, NULL, GET_OSC, /* GET_COLOR_22 */
         "color22",
         NULL, NULL},

        {4, 23, NULL, GET_OSC, /* GET_COLOR_23 */
         "color23",
         NULL, NULL},

        {4, 24, NULL, GET_OSC, /* GET_COLOR_24 */
         "color24",
         NULL, NULL},

        {4, 25, NULL, GET_OSC, /* GET_COLOR_25 */
         "color25",
         NULL, NULL},

        {4, 26, NULL, GET_OSC, /* GET_COLOR_26 */
         "color26",
         NULL, NULL},

        {4, 27, NULL, GET_OSC, /* GET_COLOR_27 */
         "color27",
         NULL, NULL},

        {4, 28, NULL, GET_OSC, /* GET_COLOR_28 */
         "color28",
         NULL, NULL},

        {4, 29, NULL, GET_OSC, /* GET_COLOR_29 */
         "color29",
         NULL, NULL},

        {4, 30, NULL, GET_OSC, /* GET_COLOR_30 */
         "color30",
         NULL, NULL},

        {4, 31, NULL, GET_OSC, /* GET_COLOR_31 */
         "color31",
         NULL, NULL},

        {4, 32, NULL, GET_OSC, /* GET_COLOR_32 */
         "color32",
         NULL, NULL},

        {4, 33, NULL, GET_OSC, /* GET_COLOR_33 */
         "color33",
         NULL, NULL},

        {4, 34, NULL, GET_OSC, /* GET_COLOR_34 */
         "color34",
         NULL, NULL},

        {4, 35, NULL, GET_OSC, /* GET_COLOR_35 */
         "color35",
         NULL, NULL},

        {4, 36, NULL, GET_OSC, /* GET_COLOR_36 */
         "color36",
         NULL, NULL},

        {4, 37, NULL, GET_OSC, /* GET_COLOR_37 */
         "color37",
         NULL, NULL},

        {4, 38, NULL, GET_OSC, /* GET_COLOR_38 */
         "color38",
         NULL, NULL},

        {4, 39, NULL, GET_OSC, /* GET_COLOR_39 */
         "color39",
         NULL, NULL},

        {4, 40, NULL, GET_OSC, /* GET_COLOR_40 */
         "color40",
         NULL, NULL},

        {4, 41, NULL, GET_OSC, /* GET_COLOR_41 */
         "color41",
         NULL, NULL},

        {4, 42, NULL, GET_OSC, /* GET_COLOR_42 */
         "color42",
         NULL, NULL},

        {4, 43, NULL, GET_OSC, /* GET_COLOR_43 */
         "color43",
         NULL, NULL},

        {4, 44, NULL, GET_OSC, /* GET_COLOR_44 */
         "color44",
         NULL, NULL},

        {4, 45, NULL, GET_OSC, /* GET_COLOR_45 */
         "color45",
         NULL, NULL},

        {4, 46, NULL, GET_OSC, /* GET_COLOR_46 */
         "color46",
         NULL, NULL},

        {4, 47, NULL, GET_OSC, /* GET_COLOR_47 */
         "color47",
         NULL, NULL},

        {4, 48, NULL, GET_OSC, /* GET_COLOR_48 */
         "color48",
         NULL, NULL},

        {4, 49, NULL, GET_OSC, /* GET_COLOR_49 */
         "color49",
         NULL, NULL},

        {4, 50, NULL, GET_OSC, /* GET_COLOR_50 */
         "color50",
         NULL, NULL},

        {4, 51, NULL, GET_OSC, /* GET_COLOR_51 */
         "color51",
         NULL, NULL},

        {4, 52, NULL, GET_OSC, /* GET_COLOR_52 */
         "color52",
         NULL, NULL},

        {4, 53, NULL, GET_OSC, /* GET_COLOR_53 */
         "color53",
         NULL, NULL},

        {4, 54, NULL, GET_OSC, /* GET_COLOR_54 */
         "color54",
         NULL, NULL},

        {4, 55, NULL, GET_OSC, /* GET_COLOR_55 */
         "color55",
         NULL, NULL},

        {4, 56, NULL, GET_OSC, /* GET_COLOR_56 */
         "color56",
         NULL, NULL},

        {4, 57, NULL, GET_OSC, /* GET_COLOR_57 */
         "color57",
         NULL, NULL},

        {4, 58, NULL, GET_OSC, /* GET_COLOR_58 */
         "color58",
         NULL, NULL},

        {4, 59, NULL, GET_OSC, /* GET_COLOR_59 */
         "color59",
         NULL, NULL},

        {4, 60, NULL, GET_OSC, /* GET_COLOR_60 */
         "color60",
         NULL, NULL},

        {4, 61, NULL, GET_OSC, /* GET_COLOR_61 */
         "color61",
         NULL, NULL},

        {4, 62, NULL, GET_OSC, /* GET_COLOR_62 */
         "color62",
         NULL, NULL},

        {4, 63, NULL, GET_OSC, /* GET_COLOR_63 */
         "color63",
         NULL, NULL},

        {4, 64, NULL, GET_OSC, /* GET_COLOR_64 */
         "color64",
         NULL, NULL},

        {4, 65, NULL, GET_OSC, /* GET_COLOR_65 */
         "color65",
         NULL, NULL},

        {4, 66, NULL, GET_OSC, /* GET_COLOR_66 */
         "color66",
         NULL, NULL},

        {4, 67, NULL, GET_OSC, /* GET_COLOR_67 */
         "color67",
         NULL, NULL},

        {4, 68, NULL, GET_OSC, /* GET_COLOR_68 */
         "color68",
         NULL, NULL},

        {4, 69, NULL, GET_OSC, /* GET_COLOR_69 */
         "color69",
         NULL, NULL},

        {4, 70, NULL, GET_OSC, /* GET_COLOR_70 */
         "color70",
         NULL, NULL},

        {4, 71, NULL, GET_OSC, /* GET_COLOR_71 */
         "color71",
         NULL, NULL},

        {4, 72, NULL, GET_OSC, /* GET_COLOR_72 */
         "color72",
         NULL, NULL},

        {4, 73, NULL, GET_OSC, /* GET_COLOR_73 */
         "color73",
         NULL, NULL},

        {4, 74, NULL, GET_OSC, /* GET_COLOR_74 */
         "color74",
         NULL, NULL},

        {4, 75, NULL, GET_OSC, /* GET_COLOR_75 */
         "color75",
         NULL, NULL},

        {4, 76, NULL, GET_OSC, /* GET_COLOR_76 */
         "color76",
         NULL, NULL},

        {4, 77, NULL, GET_OSC, /* GET_COLOR_77 */
         "color77",
         NULL, NULL},

        {4, 78, NULL, GET_OSC, /* GET_COLOR_78 */
         "color78",
         NULL, NULL},

        {4, 79, NULL, GET_OSC, /* GET_COLOR_79 */
         "color79",
         NULL, NULL},

        {4, 80, NULL, GET_OSC, /* GET_COLOR_80 */
         "color80",
         NULL, NULL},

        {4, 81, NULL, GET_OSC, /* GET_COLOR_81 */
         "color81",
         NULL, NULL},

        {4, 82, NULL, GET_OSC, /* GET_COLOR_82 */
         "color82",
         NULL, NULL},

        {4, 83, NULL, GET_OSC, /* GET_COLOR_83 */
         "color83",
         NULL, NULL},

        {4, 84, NULL, GET_OSC, /* GET_COLOR_84 */
         "color84",
         NULL, NULL},

        {4, 85, NULL, GET_OSC, /* GET_COLOR_85 */
         "color85",
         NULL, NULL},

        {4, 86, NULL, GET_OSC, /* GET_COLOR_86 */
         "color86",
         NULL, NULL},

        {4, 87, NULL, GET_OSC, /* GET_COLOR_87 */
         "color87",
         NULL, NULL},

        {4, 88, NULL, GET_OSC, /* GET_COLOR_88 */
         "color88",
         NULL, NULL},

        {4, 89, NULL, GET_OSC, /* GET_COLOR_89 */
         "color89",
         NULL, NULL},

        {4, 90, NULL, GET_OSC, /* GET_COLOR_90 */
         "color90",
         NULL, NULL},

        {4, 91, NULL, GET_OSC, /* GET_COLOR_91 */
         "color91",
         NULL, NULL},

        {4, 92, NULL, GET_OSC, /* GET_COLOR_92 */
         "color92",
         NULL, NULL},

        {4, 93, NULL, GET_OSC, /* GET_COLOR_93 */
         "color93",
         NULL, NULL},

        {4, 94, NULL, GET_OSC, /* GET_COLOR_94 */
         "color94",
         NULL, NULL},

        {4, 95, NULL, GET_OSC, /* GET_COLOR_95 */
         "color95",
         NULL, NULL},

        {4, 96, NULL, GET_OSC, /* GET_COLOR_96 */
         "color96",
         NULL, NULL},

        {4, 97, NULL, GET_OSC, /* GET_COLOR_97 */
         "color97",
         NULL, NULL},

        {4, 98, NULL, GET_OSC, /* GET_COLOR_98 */
         "color98",
         NULL, NULL},

        {4, 99, NULL, GET_OSC, /* GET_COLOR_99 */
         "color99",
         NULL, NULL},

        {4, 100, NULL, GET_OSC, /* GET_COLOR_100 */
         "color100",
         NULL, NULL},

        {4, 101, NULL, GET_OSC, /* GET_COLOR_101 */
         "color101",
         NULL, NULL},

        {4, 102, NULL, GET_OSC, /* GET_COLOR_102 */
         "color102",
         NULL, NULL},

        {4, 103, NULL, GET_OSC, /* GET_COLOR_103 */
         "color103",
         NULL, NULL},

        {4, 104, NULL, GET_OSC, /* GET_COLOR_104 */
         "color104",
         NULL, NULL},

        {4, 105, NULL, GET_OSC, /* GET_COLOR_105 */
         "color105",
         NULL, NULL},

        {4, 106, NULL, GET_OSC, /* GET_COLOR_106 */
         "color106",
         NULL, NULL},

        {4, 107, NULL, GET_OSC, /* GET_COLOR_107 */
         "color107",
         NULL, NULL},

        {4, 108, NULL, GET_OSC, /* GET_COLOR_108 */
         "color108",
         NULL, NULL},

        {4, 109, NULL, GET_OSC, /* GET_COLOR_109 */
         "color109",
         NULL, NULL},

        {4, 110, NULL, GET_OSC, /* GET_COLOR_110 */
         "color110",
         NULL, NULL},

        {4, 111, NULL, GET_OSC, /* GET_COLOR_111 */
         "color111",
         NULL, NULL},

        {4, 112, NULL, GET_OSC, /* GET_COLOR_112 */
         "color112",
         NULL, NULL},

        {4, 113, NULL, GET_OSC, /* GET_COLOR_113 */
         "color113",
         NULL, NULL},

        {4, 114, NULL, GET_OSC, /* GET_COLOR_114 */
         "color114",
         NULL, NULL},

        {4, 115, NULL, GET_OSC, /* GET_COLOR_115 */
         "color115",
         NULL, NULL},

        {4, 116, NULL, GET_OSC, /* GET_COLOR_116 */
         "color116",
         NULL, NULL},

        {4, 117, NULL, GET_OSC, /* GET_COLOR_117 */
         "color117",
         NULL, NULL},

        {4, 118, NULL, GET_OSC, /* GET_COLOR_118 */
         "color118",
         NULL, NULL},

        {4, 119, NULL, GET_OSC, /* GET_COLOR_119 */
         "color119",
         NULL, NULL},

        {4, 120, NULL, GET_OSC, /* GET_COLOR_120 */
         "color120",
         NULL, NULL},

        {4, 121, NULL, GET_OSC, /* GET_COLOR_121 */
         "color121",
         NULL, NULL},

        {4, 122, NULL, GET_OSC, /* GET_COLOR_122 */
         "color122",
         NULL, NULL},

        {4, 123, NULL, GET_OSC, /* GET_COLOR_123 */
         "color123",
         NULL, NULL},

        {4, 124, NULL, GET_OSC, /* GET_COLOR_124 */
         "color124",
         NULL, NULL},

        {4, 125, NULL, GET_OSC, /* GET_COLOR_125 */
         "color125",
         NULL, NULL},

        {4, 126, NULL, GET_OSC, /* GET_COLOR_126 */
         "color126",
         NULL, NULL},

        {4, 127, NULL, GET_OSC, /* GET_COLOR_127 */
         "color127",
         NULL, NULL},

        {4, 128, NULL, GET_OSC, /* GET_COLOR_128 */
         "color128",
         NULL, NULL},

        {4, 129, NULL, GET_OSC, /* GET_COLOR_129 */
         "color129",
         NULL, NULL},

        {4, 130, NULL, GET_OSC, /* GET_COLOR_130 */
         "color130",
         NULL, NULL},

        {4, 131, NULL, GET_OSC, /* GET_COLOR_131 */
         "color131",
         NULL, NULL},

        {4, 132, NULL, GET_OSC, /* GET_COLOR_132 */
         "color132",
         NULL, NULL},

        {4, 133, NULL, GET_OSC, /* GET_COLOR_133 */
         "color133",
         NULL, NULL},

        {4, 134, NULL, GET_OSC, /* GET_COLOR_134 */
         "color134",
         NULL, NULL},

        {4, 135, NULL, GET_OSC, /* GET_COLOR_135 */
         "color135",
         NULL, NULL},

        {4, 136, NULL, GET_OSC, /* GET_COLOR_136 */
         "color136",
         NULL, NULL},

        {4, 137, NULL, GET_OSC, /* GET_COLOR_137 */
         "color137",
         NULL, NULL},

        {4, 138, NULL, GET_OSC, /* GET_COLOR_138 */
         "color138",
         NULL, NULL},

        {4, 139, NULL, GET_OSC, /* GET_COLOR_139 */
         "color139",
         NULL, NULL},

        {4, 140, NULL, GET_OSC, /* GET_COLOR_140 */
         "color140",
         NULL, NULL},

        {4, 141, NULL, GET_OSC, /* GET_COLOR_141 */
         "color141",
         NULL, NULL},

        {4, 142, NULL, GET_OSC, /* GET_COLOR_142 */
         "color142",
         NULL, NULL},

        {4, 143, NULL, GET_OSC, /* GET_COLOR_143 */
         "color143",
         NULL, NULL},

        {4, 144, NULL, GET_OSC, /* GET_COLOR_144 */
         "color144",
         NULL, NULL},

        {4, 145, NULL, GET_OSC, /* GET_COLOR_145 */
         "color145",
         NULL, NULL},

        {4, 146, NULL, GET_OSC, /* GET_COLOR_146 */
         "color146",
         NULL, NULL},

        {4, 147, NULL, GET_OSC, /* GET_COLOR_147 */
         "color147",
         NULL, NULL},

        {4, 148, NULL, GET_OSC, /* GET_COLOR_148 */
         "color148",
         NULL, NULL},

        {4, 149, NULL, GET_OSC, /* GET_COLOR_149 */
         "color149",
         NULL, NULL},

        {4, 150, NULL, GET_OSC, /* GET_COLOR_150 */
         "color150",
         NULL, NULL},

        {4, 151, NULL, GET_OSC, /* GET_COLOR_151 */
         "color151",
         NULL, NULL},

        {4, 152, NULL, GET_OSC, /* GET_COLOR_152 */
         "color152",
         NULL, NULL},

        {4, 153, NULL, GET_OSC, /* GET_COLOR_153 */
         "color153",
         NULL, NULL},

        {4, 154, NULL, GET_OSC, /* GET_COLOR_154 */
         "color154",
         NULL, NULL},

        {4, 155, NULL, GET_OSC, /* GET_COLOR_155 */
         "color155",
         NULL, NULL},

        {4, 156, NULL, GET_OSC, /* GET_COLOR_156 */
         "color156",
         NULL, NULL},

        {4, 157, NULL, GET_OSC, /* GET_COLOR_157 */
         "color157",
         NULL, NULL},

        {4, 158, NULL, GET_OSC, /* GET_COLOR_158 */
         "color158",
         NULL, NULL},

        {4, 159, NULL, GET_OSC, /* GET_COLOR_159 */
         "color159",
         NULL, NULL},

        {4, 160, NULL, GET_OSC, /* GET_COLOR_160 */
         "color160",
         NULL, NULL},

        {4, 161, NULL, GET_OSC, /* GET_COLOR_161 */
         "color161",
         NULL, NULL},

        {4, 162, NULL, GET_OSC, /* GET_COLOR_162 */
         "color162",
         NULL, NULL},

        {4, 163, NULL, GET_OSC, /* GET_COLOR_163 */
         "color163",
         NULL, NULL},

        {4, 164, NULL, GET_OSC, /* GET_COLOR_164 */
         "color164",
         NULL, NULL},

        {4, 165, NULL, GET_OSC, /* GET_COLOR_165 */
         "color165",
         NULL, NULL},

        {4, 166, NULL, GET_OSC, /* GET_COLOR_166 */
         "color166",
         NULL, NULL},

        {4, 167, NULL, GET_OSC, /* GET_COLOR_167 */
         "color167",
         NULL, NULL},

        {4, 168, NULL, GET_OSC, /* GET_COLOR_168 */
         "color168",
         NULL, NULL},

        {4, 169, NULL, GET_OSC, /* GET_COLOR_169 */
         "color169",
         NULL, NULL},

        {4, 170, NULL, GET_OSC, /* GET_COLOR_170 */
         "color170",
         NULL, NULL},

        {4, 171, NULL, GET_OSC, /* GET_COLOR_171 */
         "color171",
         NULL, NULL},

        {4, 172, NULL, GET_OSC, /* GET_COLOR_172 */
         "color172",
         NULL, NULL},

        {4, 173, NULL, GET_OSC, /* GET_COLOR_173 */
         "color173",
         NULL, NULL},

        {4, 174, NULL, GET_OSC, /* GET_COLOR_174 */
         "color174",
         NULL, NULL},

        {4, 175, NULL, GET_OSC, /* GET_COLOR_175 */
         "color175",
         NULL, NULL},

        {4, 176, NULL, GET_OSC, /* GET_COLOR_176 */
         "color176",
         NULL, NULL},

        {4, 177, NULL, GET_OSC, /* GET_COLOR_177 */
         "color177",
         NULL, NULL},

        {4, 178, NULL, GET_OSC, /* GET_COLOR_178 */
         "color178",
         NULL, NULL},

        {4, 179, NULL, GET_OSC, /* GET_COLOR_179 */
         "color179",
         NULL, NULL},

        {4, 180, NULL, GET_OSC, /* GET_COLOR_180 */
         "color180",
         NULL, NULL},

        {4, 181, NULL, GET_OSC, /* GET_COLOR_181 */
         "color181",
         NULL, NULL},

        {4, 182, NULL, GET_OSC, /* GET_COLOR_182 */
         "color182",
         NULL, NULL},

        {4, 183, NULL, GET_OSC, /* GET_COLOR_183 */
         "color183",
         NULL, NULL},

        {4, 184, NULL, GET_OSC, /* GET_COLOR_184 */
         "color184",
         NULL, NULL},

        {4, 185, NULL, GET_OSC, /* GET_COLOR_185 */
         "color185",
         NULL, NULL},

        {4, 186, NULL, GET_OSC, /* GET_COLOR_186 */
         "color186",
         NULL, NULL},

        {4, 187, NULL, GET_OSC, /* GET_COLOR_187 */
         "color187",
         NULL, NULL},

        {4, 188, NULL, GET_OSC, /* GET_COLOR_188 */
         "color188",
         NULL, NULL},

        {4, 189, NULL, GET_OSC, /* GET_COLOR_189 */
         "color189",
         NULL, NULL},

        {4, 190, NULL, GET_OSC, /* GET_COLOR_190 */
         "color190",
         NULL, NULL},

        {4, 191, NULL, GET_OSC, /* GET_COLOR_191 */
         "color191",
         NULL, NULL},

        {4, 192, NULL, GET_OSC, /* GET_COLOR_192 */
         "color192",
         NULL, NULL},

        {4, 193, NULL, GET_OSC, /* GET_COLOR_193 */
         "color193",
         NULL, NULL},

        {4, 194, NULL, GET_OSC, /* GET_COLOR_194 */
         "color194",
         NULL, NULL},

        {4, 195, NULL, GET_OSC, /* GET_COLOR_195 */
         "color195",
         NULL, NULL},

        {4, 196, NULL, GET_OSC, /* GET_COLOR_196 */
         "color196",
         NULL, NULL},

        {4, 197, NULL, GET_OSC, /* GET_COLOR_197 */
         "color197",
         NULL, NULL},

        {4, 198, NULL, GET_OSC, /* GET_COLOR_198 */
         "color198",
         NULL, NULL},

        {4, 199, NULL, GET_OSC, /* GET_COLOR_199 */
         "color199",
         NULL, NULL},

        {4, 200, NULL, GET_OSC, /* GET_COLOR_200 */
         "color200",
         NULL, NULL},

        {4, 201, NULL, GET_OSC, /* GET_COLOR_201 */
         "color201",
         NULL, NULL},

        {4, 202, NULL, GET_OSC, /* GET_COLOR_202 */
         "color202",
         NULL, NULL},

        {4, 203, NULL, GET_OSC, /* GET_COLOR_203 */
         "color203",
         NULL, NULL},

        {4, 204, NULL, GET_OSC, /* GET_COLOR_204 */
         "color204",
         NULL, NULL},

        {4, 205, NULL, GET_OSC, /* GET_COLOR_205 */
         "color205",
         NULL, NULL},

        {4, 206, NULL, GET_OSC, /* GET_COLOR_206 */
         "color206",
         NULL, NULL},

        {4, 207, NULL, GET_OSC, /* GET_COLOR_207 */
         "color207",
         NULL, NULL},

        {4, 208, NULL, GET_OSC, /* GET_COLOR_208 */
         "color208",
         NULL, NULL},

        {4, 209, NULL, GET_OSC, /* GET_COLOR_209 */
         "color209",
         NULL, NULL},

        {4, 210, NULL, GET_OSC, /* GET_COLOR_210 */
         "color210",
         NULL, NULL},

        {4, 211, NULL, GET_OSC, /* GET_COLOR_211 */
         "color211",
         NULL, NULL},

        {4, 212, NULL, GET_OSC, /* GET_COLOR_212 */
         "color212",
         NULL, NULL},

        {4, 213, NULL, GET_OSC, /* GET_COLOR_213 */
         "color213",
         NULL, NULL},

        {4, 214, NULL, GET_OSC, /* GET_COLOR_214 */
         "color214",
         NULL, NULL},

        {4, 215, NULL, GET_OSC, /* GET_COLOR_215 */
         "color215",
         NULL, NULL},

        {4, 216, NULL, GET_OSC, /* GET_COLOR_216 */
         "color216",
         NULL, NULL},

        {4, 217, NULL, GET_OSC, /* GET_COLOR_217 */
         "color217",
         NULL, NULL},

        {4, 218, NULL, GET_OSC, /* GET_COLOR_218 */
         "color218",
         NULL, NULL},

        {4, 219, NULL, GET_OSC, /* GET_COLOR_219 */
         "color219",
         NULL, NULL},

        {4, 220, NULL, GET_OSC, /* GET_COLOR_220 */
         "color220",
         NULL, NULL},

        {4, 221, NULL, GET_OSC, /* GET_COLOR_221 */
         "color221",
         NULL, NULL},

        {4, 222, NULL, GET_OSC, /* GET_COLOR_222 */
         "color222",
         NULL, NULL},

        {4, 223, NULL, GET_OSC, /* GET_COLOR_223 */
         "color223",
         NULL, NULL},

        {4, 224, NULL, GET_OSC, /* GET_COLOR_224 */
         "color224",
         NULL, NULL},

        {4, 225, NULL, GET_OSC, /* GET_COLOR_225 */
         "color225",
         NULL, NULL},

        {4, 226, NULL, GET_OSC, /* GET_COLOR_226 */
         "color226",
         NULL, NULL},

        {4, 227, NULL, GET_OSC, /* GET_COLOR_227 */
         "color227",
         NULL, NULL},

        {4, 228, NULL, GET_OSC, /* GET_COLOR_228 */
         "color228",
         NULL, NULL},

        {4, 229, NULL, GET_OSC, /* GET_COLOR_229 */
         "color229",
         NULL, NULL},

        {4, 230, NULL, GET_OSC, /* GET_COLOR_230 */
         "color230",
         NULL, NULL},

        {4, 231, NULL, GET_OSC, /* GET_COLOR_231 */
         "color231",
         NULL, NULL},

        {4, 232, NULL, GET_OSC, /* GET_COLOR_232 */
         "color232",
         NULL, NULL},

        {4, 233, NULL, GET_OSC, /* GET_COLOR_233 */
         "color233",
         NULL, NULL},

        {4, 234, NULL, GET_OSC, /* GET_COLOR_234 */
         "color234",
         NULL, NULL},

        {4, 235, NULL, GET_OSC, /* GET_COLOR_235 */
         "color235",
         NULL, NULL},

        {4, 236, NULL, GET_OSC, /* GET_COLOR_236 */
         "color236",
         NULL, NULL},

        {4, 237, NULL, GET_OSC, /* GET_COLOR_237 */
         "color237",
         NULL, NULL},

        {4, 238, NULL, GET_OSC, /* GET_COLOR_238 */
         "color238",
         NULL, NULL},

        {4, 239, NULL, GET_OSC, /* GET_COLOR_239 */
         "color239",
         NULL, NULL},

        {4, 240, NULL, GET_OSC, /* GET_COLOR_240 */
         "color240",
         NULL, NULL},

        {4, 241, NULL, GET_OSC, /* GET_COLOR_241 */
         "color241",
         NULL, NULL},

        {4, 242, NULL, GET_OSC, /* GET_COLOR_242 */
         "color242",
         NULL, NULL},

        {4, 243, NULL, GET_OSC, /* GET_COLOR_243 */
         "color243",
         NULL, NULL},

        {4, 244, NULL, GET_OSC, /* GET_COLOR_244 */
         "color244",
         NULL, NULL},

        {4, 245, NULL, GET_OSC, /* GET_COLOR_245 */
         "color245",
         NULL, NULL},

        {4, 246, NULL, GET_OSC, /* GET_COLOR_246 */
         "color246",
         NULL, NULL},

        {4, 247, NULL, GET_OSC, /* GET_COLOR_247 */
         "color247",
         NULL, NULL},

        {4, 248, NULL, GET_OSC, /* GET_COLOR_248 */
         "color248",
         NULL, NULL},

        {4, 249, NULL, GET_OSC, /* GET_COLOR_249 */
         "color249",
         NULL, NULL},

        {4, 250, NULL, GET_OSC, /* GET_COLOR_250 */
         "color250",
         NULL, NULL},

        {4, 251, NULL, GET_OSC, /* GET_COLOR_251 */
         "color251",
         NULL, NULL},

        {4, 252, NULL, GET_OSC, /* GET_COLOR_252 */
         "color252",
         NULL, NULL},

        {4, 253, NULL, GET_OSC, /* GET_COLOR_253 */
         "color253",
         NULL, NULL},

        {4, 254, NULL, GET_OSC, /* GET_COLOR_254 */
         "color254",
         NULL, NULL},

        {4, 255, NULL, GET_OSC, /* GET_COLOR_255 */
         "color255",
         NULL, NULL},

        {17, 0, NULL, GET_OSC, /* GET_COLOR_HL */
         "highlight",
         "--get-highlight",
         "report highlight color"},

        {12, 0, NULL, GET_OSC, /* GET_CURSOR */
         "cursor",
         "--get-cursor",
         "report cursor color"},

        {13, 0, NULL, GET_OSC, /* GET_MOUSE_FG */
         "mouse-foreground",
         "--get-mouse-fg",
         "report mouse pointer foreground color"},

        {14, 0, NULL, GET_OSC, /* GET_MOUSE_BG */
         "mouse-background",
         "--get-mouse-bg",
         "report mouse pointer background color"},

        {50, 0, NULL, GET_OSC, /* GET_FONT */
         "font",
         "--get-font",
         "report font"},

        {21, 0, NULL, GET_CSI, /* GET_TITLE */
         "title",
         "--get-title",
         "report window title"},

        {18, 13, NULL, GET_CSI, /* GET_GEOMETRY */
         "geometry",
         "--get-geometry",
         "report size and position"},

        {9, 1, NULL, CSI, NULL, /* MAXIMIZE */
         "--maximize",
         "maximize window"},

        {9, 0, NULL, CSI, NULL, /* RESTORE */
         "--restore",
         "restore maximized window"},

        {2, 0, NULL, CSI, NULL, /* ICONIFY */
         "--iconify",
         "iconify window"},

        {1, 0, NULL, CSI, NULL, /* DE_ICONIFY */
         "--de-iconify",
         "de-iconify window"},

        {5, 0, NULL, CSI, NULL, /* RAISE */
         "--raise",
         "raise window"},

        {6, 0, NULL, CSI, NULL, /* LOWER */
         "--lower",
         "lower window"},

        {0, 0, NULL, ANY, NULL, /* RESET */
         "--reset",
         "full reset"},

        {0, 0, NULL, ANY, NULL, /* RAW */
         "--raw=CTLSEQS",
         "issue raw control sequence"},

        {0, 0, NULL, ANY, NULL, /* FILE_CONF */
         "--file=FILE",
         "alternative configuration file"}};

#endif
