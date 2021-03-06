class Painter {
    public:
        virtual ~Painter() = default;

        void paintCube(unsigned int layer, unsigned char* layerData, unsigned int size) const;

   protected:
        virtual void initPaint() const = 0;
        virtual void shiftOut(unsigned char data) const = 0;
        virtual void dataReady() const = 0;

        unsigned char setBit(unsigned int bit) const;
};

class PigpioPainter : public Painter {
    public:
        PigpioPainter(unsigned int outputReadyPin, unsigned int outputPin, unsigned int clockPin) : OUTPUT_READY(outputReadyPin), OUTPUT(outputPin), CLOCK(clockPin) {};

    protected:
        void initPaint() const override;
        void shiftOut(unsigned char data) const override;
        void dataReady() const override;


    private:
        const unsigned int OUTPUT_READY;
        const unsigned int OUTPUT;
        const unsigned int CLOCK;
};
