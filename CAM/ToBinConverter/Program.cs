﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ToBinConverter
{
    class Program
    {
        static string text = "255 216 255 219 0 132 0 13 9 9 11 10 8 13 11 10 11 14 14 13 15 19 32 21 19 18 18 19 39 28 30 23 32 46 41 49 48 46 41 45 44 51 58 74 62 51 54 70 55 44 45 64 87 65 70 76 78 82 83 82 50 62 90 97 90 80 96 74 81 82 79 1 14 14 14 19 17 19 38 21 21 38 79 53 45 53 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 79 255 196 1 162 0 0 1 5 1 1 1 1 1 1 0 0 0 0 0 0 0 0 1 2 3 4 5 6 7 8 9 10 11 16 0 2 1 3 3 2 4 3 5 5 4 4 0 0 1 125 1 2 3 0 4 17 5 18 33 49 65 6 19 81 97 7 34 113 20 50 129 145 161 8 35 66 177 193 21 82 209 240 36 51 98 114 130 9 10 22 23 24 25 26 37 38 39 40 41 42 52 53 54 55 56 57 58 67 68 69 70 71 72 73 74 83 84 85 86 87 88 89 90 99 100 101 102 103 104 105 106 115 116 117 118 119 120 121 122 131 132 133 134 135 136 137 138 146 147 148 149 150 151 152 153 154 162 163 164 165 166 167 168 169 170 178 179 180 181 182 183 184 185 186 194 195 196 197 198 199 200 201 202 210 211 212 213 214 215 216 217 218 225 226 227 228 229 230 231 232 233 234 241 242 243 244 245 246 247 248 249 250 1 0 3 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 1 2 3 4 5 6 7 8 9 10 11 17 0 2 1 2 4 4 3 4 7 5 4 4 0 1 2 119 0 1 2 3 17 4 5 33 49 6 18 65 81 7 97 113 19 34 50 129 8 20 66 145 161 177 193 9 35 51 82 240 21 98 114 209 10 22 36 52 225 37 241 23 24 25 26 38 39 40 41 42 53 54 55 56 57 58 67 68 69 70 71 72 73 74 83 84 85 86 87 88 89 90 99 100 101 102 103 104 105 106 115 116 117 118 119 120 121 122 130 131 132 133 134 135 136 137 138 146 147 148 149 150 151 152 153 154 162 163 164 165 166 167 168 169 170 178 179 180 181 182 183 184 185 186 194 195 196 197 198 199 200 201 202 210 211 212 213 214 215 216 217 218 226 227 228 229 230 231 232 233 234 242 243 244 245 246 247 248 249 250 255 192 0 17 8 1 224 2 128 3 1 34 0 2 17 1 3 17 1 255 218 0 12 3 1 0 2 17 3 17 0 63 0 244 250 40 162 178 246 168 124 172 40 162 138 126 210 33 102 20 81 73 83 42 171 160 212 91 22 144 144 58 154 142 73 213 114 59 138 161 113 122 72 56 60 87 60 166 217 209 10 93 201 238 110 64 24 6 178 174 39 39 60 245 164 150 124 147 218 170 59 228 212 27 165 97 146 54 73 230 160 99 79 102 168 201 160 6 26 67 74 105 166 128 16 211 77 41 164 52 12 74 67 69 20 132 37 33 165 164 52 12 109 33 31 48 96 112 195 161 20 180 26 0 216 210 60 66 214 236 33 187 201 29 3 255 0 141 117 145 76 147 32 120 216 48 62 149 231 36 2 48 64 34 173 105 218 173 214 156 113 17 47 22 121 66 113 143 165 52 200 148 20 142 245 209 92 16 195 60 98 185 253 87 72 217 153 34 25 29 197 105 105 122 205 190 161 8 100 109 174 62 242 158 48 106 251 40 101 32 244 161 165 35 36 229 77 235 177 192 203 1 82 114 8 170 236 132 87 97 168 233 33 255 0 121 24 249 177 207 189 115 183 54 141 27 97 148 138 229 157 54 142 168 77 75 99 52 173 48 173 90 120 240 125 234 38 90 200 208 174 86 128 72 169 74 211 25 106 147 96 208 3 154 41 155 72 233 74 27 214 182 141 78 228 56 142 166 154 92 230 138 213 59 146 52 211 105 212 148 192 109 37 58 144 211 66 18 146 157 73 72 97 138 40 162 129 7 122 90 40 160 2 146 150 144 245 160 97 73 75 73 64 5 20 119 162 129 9 73 138 90 74 6 33 164 165 164 160 66 81 69 6 128 18 138 40 160 4 164 52 180 80 2 82 81 69 0 37 33 165 162 152 9 73 75 73 64 5 33 162 138 0 74 74 83 72 77 0 37 37 45 37 0 20 134 138 41 136 74 67 74 105 40 16 82 81 69 0 122 224 189 99 235 79 23 164 127 14 107 60 19 78 220 105 133 145 161 246 239 106 67 126 163 181 103 150 226 153 147 64 114 163 65 181 17 216 84 50 94 179 2 50 127 58 166 88 246 166 22 61 233 14 200 154 73 201 234 73 170 239 38 115 77 102 168 217 232 1 29 189 234 22 106 29 234 54 52 134 33 52 194 105 73 230 154 77 2 16 210 26 90 74 6 52 210 26 90 67 214 128 27 138 41 105 41 8 74 67 75 72 104 24 148 134 150 144 208 2 82 82 210 80 2 46 248 229 18 194 229 28 119 29 235 164 210 60 84 164 44 26 136 43 39 64 227 36 55 214 185 202 70 80 195 12 1 250 208 38 147 220 244 132 117 145 3 35 6 83 208 138 173 123 167 199 117 25 4 97 251 48 235 92 94 155 172 93 233 143 136 207 155 1 235 27 30 159 74 236 52 221 102 211 81 136 52 50 97 187 163 112 69 104 154 150 146 57 229 9 65 222 39 63 123 166 189 187 97 191 60 86 116 145 17 156 142 107 188 154 20 153 10 184 4 26 192 191 210 90 50 89 6 83 183 173 115 212 163 213 27 211 172 165 163 57 182 74 97 90 191 36 24 39 229 63 76 85 118 143 184 174 86 154 58 55 42 149 166 21 171 5 63 58 97 20 92 100 27 72 52 6 245 169 74 211 25 106 212 154 19 87 18 147 20 152 34 140 250 241 91 70 162 123 144 226 20 148 234 74 212 145 180 82 210 80 2 82 209 69 2 10 59 210 209 72 98 119 162 150 146 128 18 142 244 180 148 0 148 82 247 164 160 4 164 167 82 83 1 180 148 234 74 0 74 74 90 49 64 9 73 78 164 160 4 164 165 164 160 66 26 74 94 244 80 3 104 165 164 166 2 26 74 113 164 160 4 164 197 45 37 0 33 164 165 52 80 3 105 13 45 20 196 37 37 45 33 160 4 52 148 180 148 8 74 41 105 40 3 214 219 79 0 241 77 251 9 207 222 53 167 73 138 211 145 156 222 212 207 26 120 232 90 143 236 225 217 170 254 197 244 160 167 167 21 54 104 165 81 25 173 167 145 208 138 173 37 171 46 114 107 100 196 79 241 84 47 110 78 115 143 165 38 139 140 209 129 34 48 205 86 98 115 91 51 218 156 100 3 143 90 161 44 29 120 164 106 153 65 141 52 251 212 210 69 131 80 26 67 18 144 208 105 51 64 5 33 160 154 74 0 67 73 75 154 67 72 66 82 98 151 52 132 208 49 41 13 45 37 0 37 37 45 20 0 148 134 150 146 128 18 138 40 160 4 166 152 240 226 72 216 199 32 57 14 189 105 244 80 51 111 76 241 108 144 149 135 83 92 175 65 50 228 147 245 21 212 195 60 55 49 7 134 69 145 15 117 53 231 68 3 193 0 212 150 87 119 90 116 190 101 140 155 87 248 162 63 117 170 227 59 110 99 58 74 90 173 206 210 255 0 74 73 144 180 64 7 174 118 226 209 163 36 56 228 112 113 91 26 79 138 109 111 89 96 156 27 123 147 252 45 247 91 232 107 86 123 56 102 82 25 23 39 156 226 156 232 198 162 247 72 141 73 83 118 145 195 188 94 181 11 33 6 186 13 67 74 104 95 35 27 27 169 3 161 246 172 185 96 42 204 181 195 58 78 44 235 140 212 150 134 121 94 105 132 85 167 142 162 43 89 26 16 17 76 43 237 83 149 166 145 77 48 32 193 20 102 165 43 76 43 87 25 180 38 147 27 73 65 4 26 51 91 42 137 238 67 136 98 138 40 197 104 154 100 216 40 162 150 128 18 138 90 40 1 180 82 209 64 13 162 151 20 80 3 105 41 212 148 0 148 148 166 138 0 109 37 58 138 96 55 20 82 210 99 52 0 148 148 234 74 4 33 20 218 117 37 0 33 20 152 167 82 98 129 141 164 52 234 67 76 67 113 69 58 147 20 0 211 73 78 164 160 6 210 83 177 73 64 13 162 150 146 152 132 164 34 148 210 80 2 82 82 209 76 71 181 209 69 21 222 121 225 69 20 81 96 10 40 162 165 193 48 184 199 64 195 154 161 117 103 142 84 86 149 33 0 140 26 231 157 43 106 141 97 81 173 206 106 88 122 224 96 253 42 148 177 99 36 87 67 121 105 130 89 122 26 201 158 44 102 176 216 235 77 53 115 48 138 109 77 34 224 241 81 26 6 54 144 210 210 26 6 54 144 211 169 40 1 180 148 234 67 72 6 208 105 105 40 64 37 37 45 20 0 134 146 150 146 128 18 142 244 26 59 208 1 73 75 69 3 10 40 162 128 27 36 105 34 225 215 62 158 213 127 77 241 5 254 154 54 57 55 118 254 142 126 117 250 26 165 69 52 218 216 78 41 232 206 235 79 213 172 117 72 179 111 38 226 57 104 219 134 95 168 164 189 210 227 156 49 81 135 60 231 222 184 61 133 101 19 67 35 195 42 244 146 51 130 43 115 78 241 116 246 202 144 234 112 153 80 113 246 136 206 78 61 89 107 101 56 205 90 103 59 165 40 187 192 73 108 165 80 236 83 27 27 99 14 217 170 143 9 219 191 28 102 186 228 107 61 78 212 203 109 50 200 142 126 242 255 0 81 89 151 90 73 130 41 11 124 202 88 16 203 252 63 133 97 87 13 214 38 176 174 182 150 231 58 209 254 117 25 74 210 146 223 124 73 34 242 196 101 133 87 104 187 215 19 139 71 66 119 41 21 166 21 171 45 31 53 25 78 188 82 69 16 21 166 149 169 138 211 10 209 112 33 35 6 140 226 164 34 154 69 90 149 133 97 51 75 77 197 38 77 90 168 197 202 63 20 148 153 165 205 90 154 100 180 20 98 140 209 87 114 68 164 197 58 138 119 1 152 162 157 138 76 80 3 104 197 56 138 76 80 3 113 65 167 82 98 128 25 70 41 212 134 152 9 73 75 138 49 64 13 197 37 58 147 20 0 148 148 234 74 0 110 40 165 160 138 4 50 138 92 81 76 6 226 146 156 105 40 1 180 132 83 141 33 160 6 226 146 157 73 64 13 197 37 59 20 148 196 52 209 75 138 49 154 46 7 180 209 69 21 232 30 112 81 69 20 0 81 69 20 0 81 69 20 0 215 80 202 84 247 172 123 203 125 164 142 192 245 173 170 173 121 22 248 201 24 207 189 114 85 133 157 205 232 206 206 199 49 58 85 86 21 126 233 10 183 214 169 56 228 214 71 89 17 164 52 226 41 8 164 3 77 52 211 200 166 226 128 26 105 41 212 148 0 218 41 105 40 1 41 41 105 40 1 40 165 197 37 32 16 210 82 209 64 9 69 20 80 8 59 209 69 20 12 40 162 138 0 5 20 80 104 1 176 153 173 103 243 236 167 104 37 255 0 103 163 125 71 122 232 244 223 24 70 231 200 213 227 88 28 240 36 92 152 219 219 218 185 234 107 170 178 149 96 8 61 65 171 140 220 72 148 20 183 59 185 180 216 39 140 201 108 85 75 142 10 242 172 43 26 230 208 196 95 124 44 184 56 233 252 171 10 194 254 251 76 144 53 148 197 162 4 230 222 86 59 57 235 143 67 93 86 149 226 123 29 71 16 78 62 207 114 120 49 75 209 191 221 61 235 71 201 87 71 185 149 167 75 109 81 134 246 252 100 126 117 11 197 131 211 154 235 46 52 72 36 86 17 51 68 79 167 34 177 110 172 164 183 153 146 104 201 7 238 56 25 200 174 90 152 86 181 70 208 175 25 104 244 49 218 58 140 165 95 146 13 174 192 212 13 30 43 149 197 163 116 202 101 105 133 106 211 71 76 104 199 97 74 224 86 219 72 86 167 41 77 43 69 198 64 86 138 148 173 52 173 59 129 29 40 167 109 164 219 77 72 86 19 52 102 138 74 181 49 114 139 154 41 40 171 82 23 40 180 148 81 84 164 77 130 146 151 189 37 59 138 193 222 146 150 146 157 192 74 74 117 37 59 128 218 41 104 160 6 210 83 177 73 76 66 98 147 20 234 74 0 110 41 49 205 58 138 0 97 20 152 167 154 74 0 102 41 49 79 197 38 41 128 202 76 84 155 115 70 206 105 92 8 241 70 218 152 37 27 42 121 135 98 32 180 161 42 93 148 161 42 28 194 199 174 209 69 21 235 158 96 81 69 20 0 81 69 20 0 81 69 20 0 82 48 202 145 140 241 75 69 103 81 94 35 139 179 57 221 69 54 179 123 26 203 113 91 154 178 252 204 125 235 21 133 113 158 130 33 34 154 69 72 69 52 138 6 48 138 105 20 242 41 184 160 6 210 26 118 41 49 72 6 210 26 119 122 74 0 109 37 58 144 208 3 104 197 45 37 0 33 164 165 239 70 40 1 41 49 75 69 0 37 20 180 80 0 41 41 104 164 1 73 75 73 64 194 146 150 146 128 16 211 37 134 57 70 36 80 195 223 181 63 189 20 1 103 79 214 245 45 49 149 82 86 186 182 29 98 144 252 192 127 178 107 172 211 124 69 166 234 140 98 141 140 114 12 126 234 112 21 142 125 61 107 137 168 229 133 36 193 97 134 95 186 195 168 250 26 210 53 28 76 231 74 50 220 244 11 141 26 214 108 149 65 27 31 226 81 205 100 220 232 115 196 140 84 151 3 129 129 214 177 236 124 71 170 216 182 36 147 237 176 247 18 147 188 125 13 117 90 95 136 116 253 73 113 12 190 92 163 25 138 95 149 191 250 245 77 194 123 153 90 165 61 181 71 53 36 12 163 37 78 62 149 1 143 38 187 169 109 97 152 31 50 53 108 214 85 215 135 131 41 48 201 243 14 128 142 43 150 116 83 216 214 24 132 244 145 203 24 249 166 20 173 121 180 169 147 239 33 28 250 85 73 45 153 73 12 57 28 116 172 29 54 142 133 36 246 40 148 166 148 171 77 25 206 49 76 41 89 187 245 25 88 173 52 173 88 41 77 41 76 101 114 180 210 181 57 90 105 90 0 132 138 76 84 165 105 165 105 166 4 121 162 158 86 154 69 62 96 104 74 40 193 162 169 72 86 10 74 40 171 82 21 130 146 138 42 185 137 176 148 81 222 131 77 72 86 18 138 40 166 152 88 74 40 162 159 48 88 74 74 118 40 197 28 194 176 218 49 79 11 74 23 154 92 193 98 61 185 165 219 82 109 165 11 80 230 59 17 237 163 109 74 22 141 181 60 227 177 24 90 93 181 32 90 80 42 121 135 98 61 180 187 105 244 82 3 213 40 162 138 247 79 36 40 162 138 0 40 162 138 0 40 162 138 0 40 162 138 153 108 192 201 214 23 31 141 97 184 228 250 86 238 177 216 123 86 25 28 87 9 232 71 100 68 69 48 138 148 138 102 40 41 17 158 180 132 83 200 164 52 128 101 52 142 105 244 132 80 3 77 52 138 125 37 0 48 210 26 117 37 0 55 20 148 234 76 80 3 113 70 41 105 40 1 40 197 45 24 160 4 52 119 162 151 20 134 37 20 98 138 0 74 41 105 40 16 148 82 210 80 49 180 82 210 80 1 73 75 70 40 1 42 57 32 142 66 11 40 220 58 48 234 42 74 40 2 229 134 189 169 233 248 81 47 218 162 254 236 199 145 244 32 87 73 166 120 174 198 243 100 114 150 130 114 62 101 113 129 159 98 107 143 166 201 18 72 48 232 172 61 197 4 202 42 91 158 152 10 186 229 72 96 123 142 106 188 250 117 188 192 101 0 35 161 244 174 2 218 242 250 201 148 218 221 200 21 127 229 153 63 41 253 43 165 177 241 149 187 225 47 162 104 100 245 80 89 127 58 12 253 155 95 11 44 92 232 43 130 200 195 241 21 147 46 157 36 100 130 167 143 65 93 100 115 193 112 21 162 150 55 4 100 109 108 212 115 162 129 187 28 30 245 156 162 153 164 103 37 185 198 189 187 43 96 131 81 180 71 39 218 186 121 173 150 80 70 213 25 57 205 82 147 78 94 112 115 143 90 197 192 213 74 230 11 39 61 233 133 43 90 91 44 96 119 244 21 89 237 152 100 96 86 110 37 92 207 43 77 41 87 26 22 29 23 138 137 163 197 32 185 88 173 48 173 89 41 76 41 64 200 10 211 74 212 229 105 165 105 220 8 74 210 98 165 43 73 182 157 192 139 20 149 38 41 54 211 76 6 82 83 177 73 138 106 66 176 218 92 82 226 129 85 204 22 27 182 157 182 157 197 20 185 197 97 161 105 66 210 210 210 114 11 9 138 80 180 180 181 55 97 97 2 210 237 163 52 110 163 86 2 224 81 76 47 72 94 154 139 11 146 100 83 75 84 101 233 165 234 148 5 114 66 212 210 213 25 122 105 122 209 68 155 158 189 69 20 87 176 121 97 69 20 80 1 69 20 80 1 69 20 80 1 69 20 84 203 102 6 78 177 219 233 88 205 90 250 191 250 193 89 44 43 136 244 35 177 17 20 210 41 230 154 105 20 48 138 105 167 145 77 52 0 195 72 105 196 82 26 64 48 210 83 205 52 208 3 77 37 58 146 128 27 73 78 52 148 0 218 74 90 40 1 180 166 138 40 4 37 20 180 148 0 82 83 169 41 0 148 119 165 164 160 4 164 52 234 111 122 6 20 148 180 80 33 41 41 104 160 98 81 69 20 0 148 82 209 64 9 72 202 24 97 128 35 222 157 73 72 6 196 173 110 225 237 220 196 65 207 201 129 91 86 94 41 184 132 121 119 145 249 137 253 224 73 53 143 73 72 14 186 13 94 214 230 50 81 142 238 192 247 21 96 149 104 213 213 129 4 113 92 72 5 91 114 18 141 234 188 26 181 111 170 93 219 156 9 11 143 67 222 165 196 14 153 128 234 61 42 19 26 247 21 159 22 180 174 70 236 130 122 131 87 126 211 20 131 116 110 8 244 168 104 162 39 129 91 160 199 181 65 37 175 61 0 171 172 71 80 65 7 161 168 201 201 197 102 208 211 51 158 223 7 24 7 240 168 76 7 210 180 200 25 197 48 160 169 104 119 50 218 34 59 84 101 43 72 196 42 39 136 122 84 140 207 41 237 77 41 237 87 90 44 84 77 30 59 80 23 42 236 166 237 171 38 58 105 74 99 43 21 230 144 173 78 82 154 82 128 32 219 73 138 152 173 52 173 49 17 81 154 126 218 105 90 6 25 163 117 33 20 152 166 128 118 250 77 244 220 82 83 208 67 183 211 75 210 82 17 84 132 41 122 105 122 66 41 49 84 132 46 234 105 108 208 105 49 84 154 16 133 169 9 165 164 167 113 30 201 69 20 87 172 121 97 69 20 80 1 69 20 80 1 69 20 80 1 69 20 84 207 225 99 91 152 186 169 204 167 218 179 90 180 53 35 254 144 195 222 179 218 184 143 65 17 17 205 52 138 121 166 210 24 194 41 166 158 69 52 208 3 13 37 56 138 105 160 6 154 74 117 52 210 1 41 166 157 77 160 4 52 134 150 146 128 18 146 150 138 0 78 244 148 180 80 2 81 69 20 0 81 69 20 128 74 40 162 129 136 105 41 77 33 160 66 81 138 90 74 6 20 148 184 164 160 2 140 81 69 0 37 20 180 148 0 81 69 20 128 74 41 105 40 1 40 162 131 72 4 32 30 212 232 230 146 54 202 55 231 73 73 64 203 176 234 82 47 202 220 140 85 168 239 131 55 60 3 233 89 20 159 78 41 114 160 55 82 117 124 224 242 40 103 247 172 101 157 193 231 154 176 183 103 28 212 56 141 51 64 154 107 26 174 46 67 1 235 138 112 147 34 179 113 29 199 154 97 81 233 70 234 92 212 52 50 50 148 195 31 181 75 158 104 197 38 130 229 115 29 48 199 86 136 166 21 30 148 134 86 49 212 101 42 217 74 97 65 78 224 85 41 233 76 41 86 204 116 194 148 1 84 173 38 218 178 99 246 166 20 166 5 114 180 221 181 57 74 105 74 96 64 69 38 42 98 148 210 180 192 139 20 132 84 133 105 184 167 112 25 138 110 42 66 41 164 83 184 134 98 147 20 252 115 72 69 59 138 199 176 209 69 21 237 30 72 81 69 20 0 81 69 20 0 81 69 20 0 81 69 33 233 81 83 225 99 91 152 122 129 205 195 253 106 139 117 171 151 156 206 213 77 171 140 244 17 25 166 154 113 166 154 6 52 211 13 60 211 13 32 26 105 167 173 56 211 77 0 33 164 165 164 52 0 218 74 90 67 64 8 105 49 75 73 64 8 105 41 123 210 82 1 40 165 164 160 2 138 41 40 0 162 138 40 0 164 165 164 164 48 164 165 164 166 2 81 69 20 0 148 81 69 32 10 74 83 69 0 37 20 180 148 0 152 162 150 146 144 5 37 45 20 0 152 160 209 65 164 2 80 104 162 128 18 128 41 216 165 11 73 200 118 27 138 80 41 216 165 2 179 148 138 72 65 144 106 69 144 211 64 165 2 178 114 41 34 85 127 122 144 54 106 1 197 40 108 84 93 133 137 193 167 10 128 73 78 18 10 90 133 137 113 72 69 48 63 189 46 224 105 216 64 69 38 40 221 70 105 242 133 198 149 164 43 78 221 77 38 159 40 174 48 173 55 109 72 77 37 22 2 34 148 194 149 57 20 148 1 92 199 76 49 213 162 180 210 180 12 168 99 166 148 230 173 149 166 148 166 23 41 148 164 219 86 154 58 97 74 119 2 177 90 110 218 176 82 154 99 162 226 61 98 138 40 175 116 242 66 138 40 160 2 138 40 160 2 138 40 160 2 145 190 233 250 82 211 95 238 55 210 179 171 240 149 31 137 24 23 7 247 141 245 170 173 214 172 204 114 198 171 181 114 29 228 102 152 105 230 152 104 24 211 76 52 243 76 52 0 211 214 155 78 52 218 64 33 164 52 166 154 104 0 166 154 90 105 160 2 146 131 69 0 37 20 148 82 0 164 165 164 160 2 138 40 52 0 148 82 210 80 1 69 20 80 2 82 82 210 80 1 73 75 73 64 5 37 45 20 134 39 74 40 162 128 10 74 83 73 64 5 20 81 72 4 162 138 40 1 40 165 165 11 73 130 27 138 80 41 192 82 129 89 185 88 164 132 197 46 41 64 165 2 178 115 41 33 49 74 5 56 10 49 89 185 92 171 9 138 90 74 66 104 73 176 20 154 105 52 132 211 115 86 162 38 199 22 164 222 125 105 164 211 11 86 138 36 220 147 205 52 162 111 122 128 177 166 150 171 80 66 185 108 74 41 124 207 122 165 184 231 52 229 147 6 142 65 92 185 187 52 102 171 137 41 225 251 230 147 136 18 230 151 53 24 127 90 80 213 60 163 184 227 65 166 230 140 243 75 148 5 164 34 151 52 153 165 96 184 152 164 34 150 138 86 1 132 82 21 167 210 26 44 4 69 105 165 106 83 73 138 6 122 109 20 81 94 233 228 133 20 81 64 5 20 81 64 5 20 81 64 5 50 67 251 182 250 26 125 71 112 113 11 125 43 42 191 9 116 254 36 96 75 212 212 13 83 73 212 212 45 214 185 78 226 51 76 52 243 76 52 12 105 166 26 121 166 26 64 52 211 77 56 211 79 90 0 105 164 52 166 144 208 2 83 105 77 33 160 4 164 165 52 148 0 148 81 73 72 2 131 69 20 0 80 104 164 160 5 164 162 138 0 40 162 138 0 74 74 83 72 104 0 164 165 52 148 12 41 41 104 164 2 81 71 122 51 64 5 20 80 104 1 40 162 138 64 20 1 154 80 41 64 169 110 195 176 128 83 177 75 138 92 86 78 69 36 38 41 113 75 74 5 98 228 82 66 98 150 146 140 226 167 113 135 74 66 105 9 164 38 173 68 77 129 52 210 104 38 154 77 104 162 38 192 154 105 52 19 76 38 180 81 37 177 75 83 115 73 154 78 245 105 8 41 41 105 40 16 30 180 26 40 166 2 102 148 49 164 164 160 9 4 134 158 178 251 213 122 51 74 192 91 223 158 244 224 194 169 135 34 156 37 52 185 70 91 221 70 234 174 37 167 137 42 92 64 151 52 102 152 28 81 186 166 192 58 146 140 210 102 149 128 90 67 70 105 13 43 1 233 180 81 69 123 103 150 20 81 69 0 20 81 69 0 20 81 69 0 21 5 217 196 13 83 213 123 227 139 115 245 21 141 109 141 41 124 70 27 247 168 77 76 253 234 22 174 99 180 140 211 13 60 211 13 3 24 105 166 156 77 52 208 3 77 50 156 105 13 32 26 105 13 41 166 154 0 74 67 75 77 160 2 155 75 222 146 144 5 37 20 119 166 1 69 20 82 0 164 165 164 160 2 138 40 160 2 138 40 160 4 164 165 164 160 2 138 13 37 0 20 81 69 33 137 69 20 80 1 69 29 232 197 0 2 148 10 80 180 224 43 57 72 105 8 5 40 20 236 81 88 202 69 164 38 41 113 75 69 100 221 202 18 140 210 19 77 38 133 27 133 197 38 155 154 66 105 51 90 198 4 182 41 52 210 104 38 155 154 209 68 155 138 77 48 154 13 37 104 144 132 52 134 150 146 129 9 73 75 73 64 5 37 41 164 160 2 138 41 40 0 52 148 180 148 192 74 40 162 128 16 210 82 154 74 96 25 32 210 239 57 235 77 164 52 8 148 75 239 79 18 213 106 51 75 149 12 180 36 167 111 170 129 241 78 18 82 229 2 206 234 93 213 92 73 78 15 83 96 61 86 138 40 175 88 243 2 138 40 160 2 138 40 160 2 138 40 160 2 170 223 159 244 124 123 213 170 167 168 156 71 138 198 182 198 180 126 35 29 250 84 45 83 61 66 213 204 118 17 154 97 167 154 97 160 99 13 52 211 141 52 208 3 13 33 165 52 211 72 4 52 211 75 72 104 1 15 90 67 69 33 160 4 52 148 180 148 0 148 81 73 64 11 69 37 45 0 37 2 150 146 144 5 20 81 64 5 20 81 64 9 73 74 105 40 0 164 162 138 0 41 41 77 20 12 41 40 167 1 72 4 197 56 45 40 90 112 21 156 164 52 132 2 150 150 138 194 82 45 32 162 151 165 52 154 203 114 133 38 154 77 33 52 210 106 212 68 216 164 211 73 230 144 154 105 53 172 98 77 197 38 147 52 153 164 173 18 38 226 230 146 138 42 144 5 54 157 77 52 192 67 73 74 105 40 1 41 41 105 41 8 74 41 105 51 64 9 69 20 83 0 164 160 209 64 9 69 20 148 196 20 148 180 148 0 148 148 180 148 0 148 148 180 148 0 82 82 211 77 0 46 105 119 211 13 20 1 236 20 81 69 122 71 154 20 81 69 0 20 81 69 0 20 81 69 0 21 71 82 63 40 21 122 179 245 35 202 253 43 10 198 212 126 35 41 234 38 169 94 161 106 192 235 35 106 105 167 154 140 245 164 49 166 152 79 52 227 77 52 48 26 105 166 148 210 26 64 52 210 82 154 105 160 4 52 134 151 189 54 128 3 73 69 37 0 20 148 180 148 0 81 69 20 0 81 69 20 0 81 69 20 0 82 81 154 41 0 26 74 40 239 64 9 69 20 80 2 81 75 79 85 164 216 13 81 82 5 165 11 138 118 43 41 72 164 132 197 20 180 149 132 164 90 65 73 154 92 211 9 168 181 202 20 154 105 57 164 38 155 154 210 48 37 177 73 166 147 70 105 164 214 209 137 45 129 52 210 104 38 146 169 33 1 165 164 239 75 76 65 69 20 80 48 166 154 117 54 152 8 105 166 156 105 166 128 10 74 13 37 33 5 20 81 64 8 104 162 146 128 14 244 119 162 146 152 5 37 45 37 2 18 138 41 41 140 41 13 45 37 2 18 146 150 131 64 13 164 52 180 148 0 82 81 69 48 61 130 138 40 175 68 243 66 138 40 160 2 138 40 160 2 138 40 160 2 179 53 51 243 129 232 43 78 178 181 3 153 72 174 122 219 155 208 220 206 106 137 170 87 53 17 172 78 161 134 163 52 243 76 52 134 48 211 13 60 211 15 90 0 109 52 211 141 52 210 1 13 52 210 210 30 148 0 211 72 69 45 37 0 37 37 41 164 160 4 162 138 78 244 0 180 82 81 64 5 45 37 45 0 37 45 20 148 0 81 69 20 0 148 157 233 105 40 0 162 129 201 169 82 63 81 74 224 34 167 175 90 148 46 41 202 184 52 236 86 82 145 105 12 197 33 167 53 55 189 97 41 20 144 148 210 105 88 211 9 168 74 227 2 105 185 160 154 105 53 172 98 38 192 154 105 52 19 77 38 181 81 33 176 205 20 148 85 136 41 40 162 128 10 40 162 144 197 162 146 138 0 41 58 82 210 119 166 2 26 105 235 75 72 122 208 2 81 69 37 33 5 37 45 37 48 10 41 13 20 0 82 82 210 80 8 41 40 163 52 0 134 146 148 210 83 0 164 52 80 105 8 74 74 90 67 76 4 164 165 52 148 192 49 73 64 165 160 15 95 162 138 43 209 60 208 162 138 40 0 162 138 40 0 162 138 40 0 172 123 243 153 216 122 26 216 172 91 211 155 135 250 215 53 93 206 154 29 74 78 106 38 169 28 243 81 26 200 232 26 105 141 78 52 211 72 99 26 152 105 237 76 52 0 211 77 165 52 211 72 4 164 52 166 155 64 8 105 15 90 83 72 104 1 166 146 148 210 26 0 59 209 69 37 0 20 81 69 0 20 180 148 80 1 69 20 80 1 69 20 148 0 148 1 147 64 25 56 29 234 212 80 96 242 57 164 221 131 113 145 69 142 79 90 157 82 164 9 129 75 140 86 82 145 105 12 198 41 134 158 198 163 99 88 74 69 36 33 53 25 52 51 83 9 169 74 227 2 105 164 208 77 52 154 218 48 37 176 38 154 122 208 77 37 106 145 44 51 77 165 164 166 32 160 209 73 64 5 20 82 80 1 222 150 146 138 67 22 138 40 160 2 154 105 198 154 105 128 134 144 210 154 109 0 20 148 81 64 132 162 138 74 0 13 37 41 164 160 2 138 40 160 4 162 138 74 0 41 13 20 83 1 40 162 146 132 32 166 210 210 80 2 26 41 113 72 105 128 82 82 210 26 4 123 5 20 81 94 137 231 5 20 81 64 5 20 81 64 5 20 81 64 8 122 26 194 186 57 153 143 189 110 63 220 111 165 96 206 127 120 79 185 174 90 159 17 213 67 98 187 117 168 137 169 26 163 53 153 184 195 76 52 243 76 52 134 48 211 77 56 211 77 0 48 211 77 56 211 77 32 16 211 77 58 154 105 128 148 148 166 154 105 0 135 173 37 41 164 160 4 162 150 138 0 74 40 163 189 0 20 81 69 0 20 82 26 40 0 160 2 78 0 230 140 115 87 45 237 182 140 159 188 127 74 77 216 22 163 97 131 111 39 239 122 213 165 76 83 214 60 82 145 138 202 82 45 33 134 163 115 79 118 197 65 35 138 194 82 44 107 53 66 207 147 197 12 196 211 73 164 149 192 51 72 105 9 166 147 91 70 36 182 4 211 73 230 130 105 43 84 172 64 82 81 65 166 2 81 69 37 0 6 138 41 13 32 14 244 148 180 148 0 180 82 80 40 24 234 41 40 160 2 144 210 211 77 0 33 164 165 166 154 4 20 148 180 148 0 82 82 210 80 1 73 75 73 64 5 37 25 162 128 10 78 244 81 76 4 61 105 41 105 40 0 164 165 164 160 66 82 82 209 76 4 162 138 40 6 37 37 41 164 160 15 96 162 138 43 209 60 208 162 138 40 0 162 138 40 0 162 138 40 1 178 125 198 250 87 63 41 203 26 222 152 226 38 62 213 129 39 36 154 228 169 241 51 174 143 194 64 221 105 134 158 213 25 168 54 67 77 48 211 141 48 208 49 166 154 105 198 154 122 210 1 166 154 105 198 154 105 0 211 72 105 77 33 160 6 210 82 154 74 46 2 82 119 165 164 160 4 164 52 180 80 2 81 69 20 0 81 69 33 160 2 142 167 2 142 248 28 154 189 105 104 70 29 198 88 244 20 155 176 9 107 107 140 49 235 87 86 60 84 139 30 41 78 0 172 165 34 210 25 210 162 118 167 72 216 170 146 203 142 252 214 50 101 4 178 1 147 215 218 171 51 19 72 88 147 205 37 74 67 12 211 73 160 154 97 53 180 98 67 98 147 77 38 144 154 43 100 172 72 102 146 138 41 128 82 82 210 82 0 205 33 165 164 164 192 41 40 160 208 2 81 69 29 232 24 10 40 162 128 10 90 41 40 0 52 134 150 144 208 3 105 9 165 164 52 8 74 40 164 160 2 140 209 69 0 37 20 82 80 1 65 162 146 128 3 73 75 73 76 64 105 40 162 128 18 146 148 210 80 1 69 20 80 2 81 69 6 152 9 77 165 164 160 71 176 209 69 21 232 158 112 81 69 20 0 81 69 20 0 81 69 20 1 13 209 196 13 88 14 121 53 187 122 113 110 107 5 205 113 203 118 118 81 248 72 152 212 102 158 213 25 169 53 26 105 166 156 77 48 210 24 134 153 78 38 154 104 1 166 154 105 198 155 72 4 52 211 74 105 13 0 37 33 162 144 208 1 73 69 37 32 10 74 90 74 96 20 81 73 64 5 25 162 173 89 218 249 141 189 199 203 216 82 1 214 86 164 157 238 63 58 213 68 199 249 233 75 28 32 1 197 72 220 10 206 82 41 33 135 2 160 149 241 239 78 146 92 85 11 155 156 124 138 114 221 205 97 41 22 132 158 124 100 14 77 85 201 61 105 40 205 74 87 24 19 197 52 154 66 105 164 214 240 137 13 129 52 210 105 9 164 173 146 177 34 209 73 69 2 22 138 74 40 24 81 69 37 32 10 74 90 74 0 41 41 105 41 0 81 69 37 0 45 20 81 64 194 138 40 160 4 52 148 185 164 52 0 134 146 131 73 64 128 210 80 104 160 4 239 69 20 80 1 73 69 20 0 82 81 69 0 37 20 82 83 0 164 165 52 148 8 41 41 105 40 0 162 138 41 128 148 148 180 218 4 20 134 138 67 76 15 98 162 138 43 208 60 224 162 138 40 0 162 138 40 0 162 138 40 2 174 160 113 108 126 181 132 245 181 169 182 32 199 189 98 57 235 92 79 115 182 159 194 136 154 152 105 205 214 152 105 26 13 52 194 105 196 211 13 33 136 105 166 150 154 77 2 16 210 26 83 77 205 33 136 105 166 148 210 19 64 8 105 40 164 205 33 5 37 4 209 64 196 162 138 41 128 82 81 82 219 192 211 200 20 125 209 212 208 3 237 45 90 118 7 31 45 109 195 110 16 0 7 2 157 107 106 35 64 0 24 2 172 28 1 89 201 148 145 17 226 171 205 46 56 29 105 211 203 180 156 26 203 185 186 228 170 117 238 107 9 50 144 183 55 60 149 78 189 51 84 232 197 21 9 92 160 38 152 77 5 169 133 171 120 68 134 192 181 48 154 9 164 173 146 177 33 154 90 74 41 128 180 102 147 52 180 128 40 164 165 52 0 82 81 154 41 0 153 162 138 74 0 40 162 146 128 10 5 20 148 128 90 90 109 45 0 45 20 148 148 12 13 37 20 80 33 13 37 20 80 2 81 69 38 104 0 61 105 41 105 41 128 81 69 20 0 148 148 189 233 40 16 82 82 210 80 1 73 75 69 3 18 138 40 166 33 41 13 41 164 205 0 33 52 148 180 148 196 37 37 4 210 26 0 246 58 40 162 189 3 206 10 40 162 128 10 40 162 128 10 40 162 147 3 63 85 63 34 138 198 106 214 213 207 221 30 223 214 177 222 184 142 232 124 40 141 169 134 156 212 195 65 99 73 166 26 82 105 166 144 9 77 165 38 154 77 0 33 52 134 130 105 9 164 49 9 164 52 26 74 4 6 146 138 74 0 59 210 81 73 64 194 138 74 80 11 48 85 25 99 64 135 69 19 75 32 69 31 90 232 44 172 68 72 6 63 31 90 110 153 166 136 144 51 14 79 83 138 212 225 70 42 27 26 35 206 209 85 174 38 0 28 30 105 215 51 133 24 7 235 88 183 151 132 146 137 212 245 172 101 34 210 11 187 172 157 136 126 166 169 129 72 6 79 243 167 244 172 183 101 136 105 140 212 172 106 38 106 218 17 33 176 99 205 70 90 130 105 181 186 86 37 139 70 105 51 69 49 10 77 20 148 3 64 14 162 144 81 222 144 197 162 146 150 128 19 52 81 73 72 2 138 41 51 64 5 20 82 80 2 147 73 69 37 32 22 150 155 70 104 1 115 205 20 148 80 1 72 104 164 160 2 146 140 210 80 1 69 20 80 2 81 222 138 74 96 45 38 104 162 129 33 40 162 138 0 41 41 105 40 0 160 209 65 160 4 164 165 52 148 192 74 67 65 164 160 65 72 77 20 134 152 1 164 160 154 67 64 30 201 69 20 87 160 121 193 69 20 80 1 69 20 80 1 69 20 82 150 192 100 235 7 231 95 97 89 46 113 90 122 187 126 244 86 83 154 226 59 227 178 35 52 198 52 226 105 140 104 40 105 166 19 74 77 52 210 1 51 77 52 166 155 154 0 9 164 38 130 105 185 164 0 77 33 52 102 155 64 10 77 38 105 51 73 64 11 73 73 70 123 208 48 39 176 228 158 213 189 162 233 12 113 44 171 243 55 35 61 133 86 208 244 183 186 144 78 192 108 254 28 255 0 58 235 227 132 68 152 29 187 210 100 57 88 131 202 242 211 218 169 93 76 171 158 106 229 221 208 69 32 98 185 141 70 252 150 40 135 62 166 176 156 141 34 187 140 190 189 44 197 16 253 77 80 3 156 210 83 192 172 119 52 20 113 72 205 65 56 168 217 171 88 68 77 136 205 81 49 161 141 52 154 232 72 128 164 162 147 189 49 11 69 37 20 192 90 90 74 41 0 160 210 210 81 72 98 209 154 74 40 0 162 138 78 244 128 13 20 82 80 1 69 20 148 0 81 69 37 32 22 140 210 81 64 11 73 73 70 104 0 52 148 81 64 1 164 162 146 154 0 162 138 74 0 40 162 146 144 11 73 69 20 196 20 81 69 0 20 148 81 64 5 37 20 153 166 1 73 74 105 180 0 102 144 209 72 77 0 37 20 26 67 76 66 26 74 40 52 1 236 180 81 69 122 7 156 20 81 69 0 20 81 69 0 20 81 69 76 246 99 91 152 90 171 102 224 143 122 205 115 205 95 213 14 110 159 62 181 158 231 154 227 59 209 25 53 27 83 218 163 52 12 105 52 194 105 77 52 210 1 13 38 104 52 134 128 19 52 153 160 210 82 0 166 230 150 155 64 5 38 104 164 160 98 212 250 125 140 151 215 75 26 169 216 15 204 123 125 42 8 227 146 105 146 8 151 46 231 31 65 235 93 198 143 165 46 159 108 20 156 185 251 199 222 141 140 229 53 18 205 157 170 219 64 177 168 3 3 28 83 231 149 99 66 79 165 61 152 40 201 174 115 91 213 72 38 40 155 158 65 246 172 231 43 10 156 92 159 51 43 106 186 142 93 150 51 214 177 122 156 158 180 22 44 114 121 52 160 102 185 155 185 212 133 81 74 78 41 122 83 29 170 225 27 137 177 24 212 76 212 172 213 25 53 208 145 12 9 164 52 19 73 154 177 5 37 20 102 128 10 41 40 160 5 205 45 37 40 164 2 230 138 76 210 210 1 104 164 205 20 12 40 164 163 52 0 81 154 76 209 154 64 20 148 185 164 164 1 69 25 164 166 1 69 25 164 164 0 104 162 147 52 192 40 164 162 144 11 73 69 37 48 22 147 233 69 20 0 148 81 69 0 20 82 210 80 32 162 138 74 0 41 40 52 83 0 52 148 82 80 1 77 52 166 146 128 19 52 132 210 147 73 64 9 154 74 9 164 166 32 38 147 52 82 80 192 246 122 40 162 189 3 206 10 40 162 128 10 40 162 128 10 40 164 61 15 210 162 167 194 199 29 206 119 81 108 220 191 214 168 49 171 119 199 55 46 106 155 87 41 222 70 198 163 52 246 168 218 144 198 154 105 165 52 210 105 0 148 218 82 105 166 128 12 210 26 13 37 32 12 211 105 77 37 0 37 35 48 80 73 165 171 186 30 154 117 29 64 51 38 235 120 78 91 61 11 112 64 170 66 148 172 141 175 11 105 38 40 126 219 58 254 242 80 10 3 216 87 71 72 0 0 0 0 3 160 21 67 85 212 210 202 44 117 145 135 2 166 110 199 52 83 169 34 158 187 170 136 65 134 38 249 199 222 199 106 229 29 217 219 45 214 157 60 237 52 133 219 169 61 234 46 181 201 39 115 190 42 200 81 201 169 5 53 69 4 209 21 113 220 86 106 133 154 149 219 154 140 154 232 140 108 102 216 19 77 38 138 74 177 5 55 52 166 146 152 0 52 103 154 78 244 80 2 230 138 74 5 0 45 45 37 20 128 90 90 74 40 1 104 162 138 64 20 148 82 80 2 210 81 73 72 98 210 81 73 72 5 52 148 102 147 52 0 185 164 162 146 128 22 146 138 40 1 40 205 20 80 1 69 20 83 16 148 180 98 138 6 37 20 81 64 130 131 70 105 13 0 20 148 180 148 192 13 37 20 148 0 180 211 74 105 180 192 51 73 65 164 52 128 67 69 33 164 205 48 3 73 154 13 37 2 2 105 40 162 128 61 162 138 40 175 64 243 130 138 40 160 2 138 40 160 2 154 255 0 113 190 148 234 108 156 70 255 0 67 89 213 248 74 135 196 142 94 228 230 102 250 213 87 53 60 231 50 53 87 99 92 167 121 25 168 205 61 141 70 77 2 26 105 180 164 211 77 33 136 105 40 52 148 128 74 66 105 115 73 64 9 154 74 90 66 112 9 52 192 110 217 37 149 32 133 75 73 35 0 0 250 245 175 64 210 180 228 211 172 99 183 76 18 7 204 64 198 79 173 96 248 67 77 44 95 82 152 96 183 203 8 255 0 103 185 174 161 220 34 51 55 69 25 53 165 148 85 206 89 201 206 92 168 130 254 241 45 45 154 70 60 255 0 8 245 53 196 94 93 201 113 51 73 35 18 204 106 222 171 169 61 220 228 145 242 3 133 83 218 178 137 174 26 146 187 59 41 193 69 8 77 42 211 69 60 84 88 208 118 113 76 102 247 161 141 68 205 91 194 36 54 4 230 155 154 51 69 106 72 132 210 80 104 52 192 76 210 102 138 74 0 40 163 52 148 0 185 162 146 138 0 92 210 131 73 75 72 5 205 20 148 185 164 8 90 41 51 69 0 20 148 19 73 154 6 45 37 20 148 128 90 41 51 73 64 133 163 52 148 80 48 162 146 150 128 18 138 40 160 2 140 209 71 122 4 20 102 138 74 0 90 74 41 41 128 180 153 162 138 0 51 69 37 20 0 102 147 52 82 19 64 11 77 205 25 244 164 160 2 144 154 13 38 104 0 205 33 52 134 146 152 1 164 205 6 146 129 1 52 148 119 164 160 5 164 205 20 134 128 61 170 138 40 175 64 243 130 138 40 160 2 138 40 160 2 163 156 226 7 250 26 146 160 188 56 182 122 202 174 197 211 248 145 203 204 126 115 205 87 106 154 67 201 53 93 143 53 204 118 140 106 97 167 55 90 140 210 1 13 52 210 158 180 210 104 1 41 9 160 154 74 67 10 74 13 33 166 1 79 180 179 151 80 212 34 179 139 161 59 164 110 193 65 21 19 184 69 44 107 174 240 158 150 109 44 13 212 195 247 247 56 99 236 59 10 210 156 111 169 149 89 217 89 27 80 66 144 66 144 196 187 81 6 213 30 213 207 107 186 153 149 154 222 19 129 25 249 129 56 220 107 83 86 212 82 218 19 24 111 222 48 232 59 10 227 238 238 140 207 150 57 62 181 134 34 166 182 67 161 78 203 153 149 221 247 28 158 190 180 204 208 78 104 29 107 148 234 21 122 211 137 197 39 74 99 181 105 5 113 49 25 169 148 103 52 149 208 180 51 10 40 205 37 0 20 148 26 76 211 1 13 37 6 147 52 0 180 148 153 162 128 22 128 105 51 70 104 1 194 140 210 81 154 0 118 105 105 162 150 144 11 154 51 73 154 76 210 1 104 205 38 105 40 1 104 164 205 25 164 1 69 20 148 0 82 210 102 138 0 40 162 140 211 0 162 138 76 210 1 115 73 69 20 0 81 73 69 48 23 52 148 82 80 1 69 25 164 205 0 20 82 81 64 1 164 205 33 52 132 208 2 230 146 138 105 166 33 77 37 20 220 208 49 73 166 147 70 105 40 1 51 71 122 41 40 16 166 155 69 20 0 102 138 74 41 136 246 186 40 162 187 207 60 40 162 138 0 40 162 138 0 42 182 160 113 104 213 102 170 106 103 22 109 245 21 141 109 141 105 124 71 44 231 230 53 3 84 206 122 138 129 141 115 157 99 9 166 19 74 77 52 210 1 9 166 208 105 9 160 4 164 162 146 129 129 52 148 102 153 44 130 52 44 123 116 161 43 232 23 45 233 22 35 81 214 97 183 113 186 24 191 121 40 199 7 29 1 174 242 234 230 59 75 115 35 253 213 24 0 10 203 240 174 155 246 45 40 75 40 253 253 199 239 36 36 99 30 131 252 250 212 26 174 163 230 9 24 15 221 161 216 185 29 79 115 90 212 151 36 108 142 104 47 105 59 189 140 157 66 229 100 145 229 63 235 36 231 61 191 10 204 38 157 35 12 240 48 5 69 222 188 231 174 167 114 86 22 156 41 131 173 60 112 40 74 224 35 54 5 68 77 12 217 52 218 233 140 108 67 98 210 81 70 106 132 20 134 138 67 64 6 105 40 205 38 105 128 134 146 131 73 64 5 25 164 205 37 48 29 154 51 77 205 25 164 3 179 75 154 102 104 205 0 60 26 80 106 61 212 185 164 3 243 73 154 110 104 221 72 7 102 140 211 119 81 154 96 59 52 148 220 210 230 144 14 205 37 38 104 205 3 22 140 210 102 138 4 46 104 164 205 25 160 2 140 209 154 74 0 90 41 40 205 0 20 81 154 74 4 46 105 41 51 70 104 24 81 73 154 76 208 2 230 144 154 67 70 104 0 38 147 52 82 102 152 6 105 9 160 210 102 128 12 210 102 144 210 102 129 11 73 69 37 0 20 148 81 222 152 48 164 160 210 80 33 105 59 209 65 160 15 108 162 138 43 188 243 194 138 40 160 2 138 40 160 2 168 106 237 139 108 123 213 250 204 214 143 238 64 172 43 27 81 248 142 109 205 64 198 165 118 235 80 49 172 14 161 166 154 105 73 166 26 64 33 52 134 131 72 104 24 134 146 148 211 77 32 22 172 232 186 119 246 166 174 177 49 253 197 191 207 46 6 114 123 10 165 44 130 56 217 219 160 253 107 174 240 252 31 217 94 31 251 76 234 76 211 254 241 151 166 73 232 43 106 106 222 243 50 170 223 194 139 218 189 228 145 34 199 3 13 197 191 121 198 112 181 203 106 119 109 52 242 96 149 86 57 42 58 26 213 212 75 173 161 185 185 85 138 73 88 124 138 217 15 254 120 174 114 71 44 114 122 250 87 37 105 185 72 218 156 20 85 134 177 166 102 130 105 7 90 196 208 120 164 118 192 197 46 112 42 22 108 154 210 156 122 137 177 59 209 73 154 43 160 128 162 138 51 72 2 147 52 19 73 154 96 6 146 130 105 51 64 8 105 51 65 52 210 104 1 115 77 205 33 52 132 211 1 115 70 105 185 164 205 0 63 52 110 166 102 140 210 2 76 210 102 153 154 51 72 9 51 70 106 61 212 110 160 9 51 70 106 61 212 110 160 9 51 70 105 153 163 52 0 252 210 230 163 205 46 104 1 249 162 154 13 0 208 3 168 205 38 105 51 72 7 230 146 147 52 102 128 23 52 83 115 70 104 1 115 73 154 76 209 154 0 92 210 82 102 140 208 1 154 51 73 154 74 96 46 105 51 73 154 66 104 1 73 164 38 140 210 102 128 2 105 40 164 160 0 154 41 58 81 64 131 52 82 26 74 96 45 37 20 148 8 40 162 146 128 22 146 131 69 0 123 109 20 81 93 231 158 20 81 69 0 20 81 69 0 21 147 174 156 34 253 63 173 107 86 38 190 223 116 123 87 61 109 209 189 13 206 121 143 25 168 154 164 99 199 21 9 53 137 210 33 166 154 83 76 38 144 8 105 13 4 210 26 6 6 146 131 76 146 65 28 108 237 208 15 206 132 174 236 12 185 162 217 13 67 93 130 22 25 138 1 231 72 49 144 112 120 31 157 117 90 180 242 220 73 246 56 64 0 124 204 196 242 113 215 30 213 91 195 150 67 76 208 222 238 229 194 205 116 4 172 113 247 120 249 71 191 95 214 161 158 219 22 247 23 10 25 139 29 198 86 126 84 122 123 230 174 180 185 87 42 50 166 185 164 228 204 221 90 75 108 170 70 25 219 110 20 183 72 249 231 30 185 172 182 52 249 27 56 57 207 29 106 18 121 174 23 169 210 149 131 60 211 150 153 78 20 34 129 206 6 7 83 81 82 179 2 196 250 211 107 166 42 200 201 234 20 81 72 106 128 90 76 210 102 138 0 13 25 164 38 147 52 88 5 38 155 154 76 210 19 64 1 52 210 105 9 166 147 76 5 38 154 77 38 234 105 60 208 3 179 73 154 110 105 51 64 14 205 25 166 238 164 205 0 63 52 187 170 61 212 110 160 87 36 221 70 234 143 117 27 169 88 46 73 154 51 81 102 148 53 22 11 146 102 141 213 30 234 92 208 50 64 105 115 81 131 75 154 64 73 154 80 106 60 210 131 76 9 51 69 51 52 185 164 3 179 70 105 185 164 205 0 59 52 102 155 154 51 64 11 154 41 51 73 154 0 118 105 51 77 205 4 208 2 230 144 154 76 210 102 128 23 52 102 146 147 52 192 92 210 81 69 32 10 76 209 73 64 130 138 51 73 154 96 20 81 73 64 130 138 51 73 76 0 210 81 154 51 64 7 74 40 164 160 15 255 217 4";

        static void Main(string[] args)
        {
            string[] values = text.Trim().Split(' ');
            
            using (FileStream stream = new FileStream("img.jpeg", FileMode.Create))
            {
                using (BinaryWriter writer = new BinaryWriter(stream))
                {
                    foreach (var val in values)
                    {
                        writer.Write(byte.Parse(val));
                    }
                    writer.Close();
                }
            }
        }
    }
}