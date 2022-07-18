require "via"

# Hardware descriptions
# VENDOR_ID       0x84E9       
# PRODUCT_ID      0x7960
# DEVICE_VER      0x0001
# MANUFACTURER    Techmech keys
# PRODUCT         OLSK60

# Initialize a Keyboard
kbd = Keyboard.new

kbd.via = true # This should happen before `kbd.init_pins`
kbd.via_layer_count = 3

# The actual pin numbers depend on your circuit
r0 = 29
r1 = 28
r2 = 27
r3 = 26
r4 = 18
r5 = 0
r6 = 1
r7 = 2
r8 = 3
r9 = 4
c0 = 10
c1 = 19
c2 = 20
c3 = 5
c4 = 7
c5 = 8

# Init nomal matrix
kbd.init_matrix_pins(
  [
    [ [r0, c0], [r0, c1], [r0, c2], [r0, c3], [r0, c4], [r0, c5], [r5, c5], [r5, c4], [r5, c3], [r5, c2], [r5, c1], [r5, c0] ],
    [ [r1, c0], [r1, c1], [r1, c2], [r1, c3], [r1, c4], [r1, c5], [r6, c5], [r6, c4], [r6, c3], [r6, c2], [r6, c1], [r6, c0] ],
    [ [r2, c0], [r2, c1], [r2, c2], [r2, c3], [r2, c4], [r2, c5], [r7, c5], [r7, c4], [r7, c3], [r7, c2], [r7, c1], [r7, c0] ],
    [ [r3, c0], [r3, c1], [r3, c2], [r3, c3], [r3, c4], [r3, c5], [r8, c5], [r8, c4], [r8, c3], [r8, c2], [r8, c1], [r8, c0] ],
    [ [r4, c0], [r4, c1], [r4, c2], [r4, c3], [r4, c4], [r4, c5], [r9, c5], [r9, c4], [r9, c3], [r9, c2], [r9, c1], [r9, c0] ],
  ]
)


rgb = RGB.new(
  9,    # pin number./
  21,    # size of undmnkerglow pixel
  1,   # size of backlighlk,t pixel
  false # 32bit data will be sent to a pixel if true while 24bit if false
)
rgb.effect     = :breath
rgb.speed      = 22  # 1-31  / default: 22
rgb.hue        = 10  # 0-100 / default: 0
rgb.saturation = 10 # 0-100 / default: 100

kbd.append rgb # `kbd` is an instance of Keyboard class that should be newed in advance

kbd.define_mode_key :VIA_FUNC0, [ Proc.new { kbd.bootsel! }, nil, 300, nil ]
kbd.define_mode_key :VIA_FUNC1, [ :KC_ENTER, :VIA_LAYER1, 150, 150 ]
kbd.define_mode_key :VIA_FUNC2, [ :KC_SPACE, :VIA_LAYER2, 150, 150 ]
kbd.define_mode_key :VIA_FUNC3, [ :KC_NO,    :VIA_LAYER3, 150, 150 ]


kbd.start!