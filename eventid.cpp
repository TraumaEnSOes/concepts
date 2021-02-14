/*
    Como generar ID automágicos para jerarquías de clases, tales como jerarquías de eventos.
    El truco está en la función plantila 'AutoId( )'. El compilador generará una nueva instancia por cada tipo pasado como argumento de plantilla.
    Esto permite declarar los distintos eventos en archivos totalmente distintos, sin problemas de solapamientos de ID, y sin necesidad de
mantener variables estáticas ni usar ningún otro truco.
*/

template< typename T > void AutoId( ) { }

struct Event {
  virtual void *eventType( ) const = 0;
};

#define BEGIN_EVENT( NAME ) \
    class NAME : public Event { \
        static void *staticEventType( ) { return reinterpret_cast< void * >( reinterpret_cast< void (*)( ) >( AutoId< NAME > ) ); } \
    public: \
        void *eventType( ) const override { return NAME::staticEventType( ); }
#define END_EVENT };

BEGIN_EVENT( Event1 )
END_EVENT

BEGIN_EVENT( Event2 )
END_EVENT

int main( ) {
    Event1 ev1;
    Event2 ev2;

    std::cout << "Event1: " << ev1.eventType( );
    std::cout << "\nEvent2: " << ev2.eventType( );

    return 0;
}
