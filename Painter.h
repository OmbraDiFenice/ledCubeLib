class Painter {
    public:
        enum ShiftMode {
            LSB_FIRST,
            MSB_FIRST
        };

        Painter(unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ) : _sizeX(sizeX), _sizeY(sizeY), _sizeZ(sizeZ) {};
        virtual ~Painter() = default;

        void paintCube(unsigned int layer, unsigned char* layerData, unsigned int size) const;

    protected:
        virtual void initPaint() const = 0;
        virtual void shiftOut(unsigned char data, ShiftMode shiftMode) const = 0;
        virtual void dataReady() const = 0;

        unsigned char getMaskForBit(unsigned int bit) const;

    protected:
        unsigned int _sizeX;
        unsigned int _sizeY;
        unsigned int _sizeZ;
};

class PigpioPainter : public Painter {
    public:
        PigpioPainter(unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ, unsigned int outputReadyPin, unsigned int outputPin, unsigned int clockPin) : Painter(sizeX, sizeY, sizeZ), OUTPUT_READY(outputReadyPin), OUTPUT(outputPin), CLOCK(clockPin) {};

    protected:
        void initPaint() const override;
        void shiftOut(unsigned char data, ShiftMode shiftMode) const override;
        void dataReady() const override;


    private:
        const unsigned int OUTPUT_READY;
        const unsigned int OUTPUT;
        const unsigned int CLOCK;
};
